/*
 * incremental.vala
 * Copyright (C) 2015 Loki Verloren <loki.verloren@gmail.com>
 *
 * Incremental is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Incremental is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

using GLib;
using Gtk;
using Gdk;

public class
Incremental : Gtk.Application
{
	public string AppName = "Incremental";
	public string Version = "0.1" ;
	public TreeStore tree_store;
	public TreeIter Root;

	protected Gtk.ScrolledWindow tree_frame;
	protected Gtk.TreeView tree_view;
	protected Gtk.Frame terminal_frame;
	protected Gtk.Button terminal_button;
	protected Gtk.Paned popup_pane;
	protected Gtk.FileChooserButton file_button;
	protected Gtk.TreeSelection tree_selection;
	protected Gtk.Box text_panel_box;

	public enum
	Columns
	{
		HEAD,
		BODY,
		N_COLUMNS
	}

	public
	Incremental ()
	{
		Object (application_id:"org.agora.incremental",
			flags:ApplicationFlags.FLAGS_NONE);
		this.tree_store =
			new TreeStore (Columns.N_COLUMNS,
				typeof (string),
				typeof (Gtk.TextBuffer)
			);
	}

	protected override void
	activate ()
	{
		var window = new ApplicationWindow (this);
		window.resize(800, 600);
		window.title = @"$AppName $Version";
		window.set_position (WindowPosition.CENTER);
		window.set_titlebar(create_headerbar ());
		window.add(create_pane ());
		window.show_all ();
	}

	protected void
	log_forwards ()
	{
		stderr.printf ("event: redo_button.clicked\n");
	}

	protected void
	log_backwards ()
	{
		stderr.printf ("event: undo_button.clicked\n");
	}

	protected void
	create_new_file ()
	{
		stderr.printf ("event: file_new.clicked\n");
	}

	protected void
	export_file ()
	{
		stderr.printf ("event: file_export.clicked\n");
	}

	protected void
	file_open ()
	{
		var uri = file_button.get_uri ();
		stderr.printf ("event: file_open.selection_changed %s\n",
			uri);
	}

	protected HeaderBar
	create_headerbar ()
	{
		var headerbar = new HeaderBar ();

		var file_box = new Box (Orientation.HORIZONTAL, 0);
		var file_new = new Button.from_icon_name ("document-new-symbolic");
		file_new.set_tooltip_text ("New document");
		file_new.clicked.connect (create_new_file);

		file_button =
			new FileChooserButton ("No file open", FileChooserAction.OPEN);
		file_button.set_tooltip_text ("Open document");
		file_button.selection_changed.connect (file_open);

		var file_export =
			new Button.from_icon_name ("document-export-symbolic");
		file_export.set_tooltip_text ("Export document");
		file_export.clicked.connect (export_file);
		file_box.add (file_new);
		file_box.add (file_button);
		file_box.add (file_export);

		headerbar.set_custom_title (file_box);
		headerbar.set_show_close_button(true);

		var hide_tree = new Button.from_icon_name ("pane-hide-symbolic");
		hide_tree.set_tooltip_text ("Hide tree");
		hide_tree.clicked.connect (hide_treeview);
		headerbar.pack_start (hide_tree);

		var tree_append = new Button.from_icon_name ("list-add-symbolic");
		tree_append.set_tooltip_text ("Append new item to tree");
		tree_append.clicked.connect (add_tree_node);
		headerbar.pack_start (tree_append);

		/*
		MenuButton  gear_menu =
			new MenuButton ();
		gear_menu.set_image (new Image.from_icon_name
		                     ("application-menu-symbolic", IconSize.BUTTON));
		headerbar.pack_end (gear_menu);
		*/

		terminal_button =
			new Button.from_icon_name ("utilities-terminal-symbolic");
		terminal_button.set_tooltip_text ("Pop up terminal");
		terminal_button.clicked.connect (hide_terminal);
		headerbar.pack_end (terminal_button);

		var redo_button = new Button.from_icon_name ("edit-redo-symbolic");
		redo_button.set_tooltip_text ("Redo");
		redo_button.clicked.connect (log_forwards);
		headerbar.pack_end (redo_button);

		var undo_button = new Button.from_icon_name ("edit-undo-symbolic");
		undo_button.set_tooltip_text ("Undo");
		undo_button.clicked.connect (log_backwards);
		headerbar.pack_end (undo_button);

		return headerbar;
	}

	protected Gtk.ScrolledWindow
	create_text_view ()
	{
		var text_panel_scrolledwindow = new Gtk.ScrolledWindow (null, null);
		var text_panel_viewport = new Gtk.Viewport (null, null);
		text_panel_box = new Gtk.Box (Gtk.Orientation.VERTICAL, 0);
		text_panel_scrolledwindow.add (text_panel_viewport);
		text_panel_viewport.add (text_panel_box);
		return text_panel_scrolledwindow;
	}

	protected Paned
	create_pane ()
	{
		popup_pane = new Paned (Orientation.VERTICAL);
		var pane = new Paned(Orientation.HORIZONTAL);
		tree_frame = new Gtk.ScrolledWindow (null, null);
		tree_frame.set_min_content_width (200);
		tree_frame.set_min_content_height (200);
		var tree_frame_viewport = new Gtk.Viewport (null, null);
		tree_frame.add (tree_frame_viewport);
		tree_frame_viewport.add (create_treeview());
		pane.add1 (tree_frame);
		pane.add2 (create_text_view ());
		popup_pane.add1 (pane);

		return popup_pane;
	}

	protected void
	hide_treeview ()
	{
		if (tree_frame.visible)
		{
			stderr.printf ("event: hide_treeview hide\n");
			tree_frame.hide ();
		} else {
			stderr.printf ("event: hide_treeview show\n");
			tree_frame.show ();
		}
	}

	protected void
	hide_terminal ()
	{
		if (terminal_frame == null)
		{
			terminal_frame = new Gtk.Frame (null);
			popup_pane.add2 (terminal_frame);
			terminal_frame.show();
			stderr.printf ("event: hide_terminal init\n");
		}
		else if (terminal_frame.visible)
		{
			stderr.printf ("event: hide_terminal hide\n");
			terminal_frame.hide ();
		} else {
			stderr.printf ("event: hide_terminal show\n");
			terminal_frame.show ();
		}
	}

	protected void
	edit_head (string path, string text)
	{
		var tree_path = new TreePath.from_string(path);
		TreeIter iter;
		tree_store.get_iter (out iter, tree_path);
		tree_store.set (iter, 0, text);
		tree_selection_changed ();
		stderr.printf ("event: edit_head (%s , \"%s\")\n",
		               path, text);
	}

	public void
	remove_text_box_child (Widget widget)
	{
		text_panel_box.remove (widget);
		stderr.printf ("callback: remove_text_box_child\n");
	}

	public bool
	node_delete_event (Gtk.Widget sender, Gdk.EventButton evt)
	{
		stderr.printf ("event: user clicked delete node\n");
		return true;
	}

	public bool
	body_edit_mode (EventButton event)
	{
		stderr.printf ("event: user clicked to edit body text\n");
		return true;
	}

	public void
	add_visible_textviews (TreeModel model, TreePath path, TreeIter iter)
	{
		var node_header_bar = new Gtk.Grid ();
		node_header_bar.orientation = Orientation.HORIZONTAL;

		string head_string;
		model.@get (iter, Columns.HEAD, out head_string);

		var node_delete_image =
			new Gtk.Image.from_icon_name("window-close-symbolic",
				IconSize.BUTTON);
		var node_delete_eventbox = new Gtk.EventBox ();
		node_delete_eventbox.add (node_delete_image);
		node_delete_image.visible = true;
		node_delete_eventbox.halign = Gtk.Align.START;
		node_delete_eventbox.button_release_event.connect
			(node_delete_event);
		node_header_bar.add (node_delete_eventbox);

		head_string = "<span color = 'gray'><i>" + head_string + 
			"</i></span>  ";
		var node_header_bar_label = new Gtk.Label (head_string);
		node_header_bar_label.use_markup = true;
		node_header_bar.add (node_header_bar_label);
			
		node_header_bar.visible = true;
		text_panel_box.add (node_header_bar);

		Gtk.TextBuffer visible_buffer;
		model.@get (iter, Columns.BODY, out visible_buffer);

//		var node_textview = new Label (visible_buffer.text);
//		node_textview.wrap = true;
		var node_textview = new TextView ();
		node_textview.buffer = visible_buffer;
		node_textview.wrap_mode = WrapMode.WORD;
		node_textview.accepts_tab = false;
		text_panel_box.add (node_textview);

		//node_textview.set_vexpand (true);

		text_panel_box.show_all();
		
		stderr.printf ("callback: add_visible_textviews\n");
	}

	protected void
	tree_selection_changed ()
	{
		int select_count;
		tree_selection = tree_view.get_selection ();
		select_count = tree_selection.count_selected_rows ();
		stderr.printf ("event: tree_selection_changed %d rows\n",
			select_count);
		text_panel_box.@foreach (remove_text_box_child);
		tree_selection.selected_foreach (add_visible_textviews);
	}

	protected TreeView
	create_treeview ()
	{
		tree_view = new TreeView ();

		tree_view.enable_tree_lines = true;
		tree_view.headers_visible = false;
		tree_view.reorderable = true;
		tree_view.activate_on_single_click = true;

		tree_view.set_model (this.tree_store);

		var node_head = new CellRendererText ();
		node_head.edited.connect (edit_head);
		node_head.editable = true;
		node_head.set_alignment (0, (float)0.5);
		tree_view.insert_column_with_attributes (Columns.HEAD, "Head",
			node_head, "text", Columns.HEAD, null);

		tree_selection = tree_view.get_selection ();
		tree_selection.changed.connect (tree_selection_changed);
		tree_selection.set_mode (Gtk.SelectionMode.MULTIPLE);

		return tree_view;
	}

	public void
	add_tree_node () {
		this.tree_store.append (out Root, null);
		var new_head = "new node head";
		var new_body_texttagtable = new Gtk.TextTagTable ();
		var new_body = new Gtk.TextBuffer (new_body_texttagtable);
		new_body.set_text ("You may wish to begin by reading the text widget conceptual overview which gives an overview of all the objects and data types related to the text widget and how they work together.");
		this.tree_store.set (Root,
			Columns.HEAD, new_head,
			Columns.BODY, new_body,
			-1);
		stderr.printf ("event: add_tree_node '%s' '%s'\n",
			new_head, new_body.text);
	}

	public static int
	main (string[] args) {
		var app = new Incremental ();
		return app.run (args);
	}

}
