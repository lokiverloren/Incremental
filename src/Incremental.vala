/*
 * Incremental.vala
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

using Gtk;
using Gdk;

public class
Incremental : Gtk.Application
{
    // Application name stuff
	public string AppName = "Incremental";
	public string Version = "0.1" ;

    // protected GUI interface objects
    protected Gtk.Grid interface_grid;

    protected Gtk.ScrolledWindow interface_tree_scroller;
    protected Gtk.Viewport interface_tree_viewport;

    protected Gtk.ScrolledWindow interface_document_scroller;
    protected Gtk.Viewport interface_document_viewport;

    protected Gtk.ScrolledWindow interface_terminal_scroller;
    protected Gtk.Viewport interface_terminal_viewport;

    protected Gtk.ScrolledWindow interface_help_scroller;
    protected Gtk.Viewport interface_help_viewport;

    protected Gtk.TreeView interface_tree_view;

    // headerbar interface elements
    protected Gtk.HeaderBar headerbar;

    protected Gtk.ToggleButton hide_tree;
    protected Gtk.Button append_node;

    protected Gtk.Box file_box;
    protected Gtk.Button file_new;
    protected Gtk.FileChooserButton file_select;
    protected Gtk.Button file_export;

    protected Gtk.Button undo;
    protected Gtk.Button redo;
    protected Gtk.ToggleButton hide_terminal;
    protected Gtk.ToggleButton hide_help;

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
	}

	protected override void
	activate ()
	{
		var window = new ApplicationWindow (this);
		window.resize(800, 600);
		window.title = @"$AppName $Version";
		window.set_position (WindowPosition.CENTER);
		window.set_titlebar(create_headerbar ());
        interface_grid = create_viewer ();

		window.add(interface_grid);

		window.show_all ();
        toggle_help();
        toggle_terminal();
	}

    protected void toggle_visible_prototype (Gtk.Widget widget)
    {
        if (widget.visible)
        {
            widget.visible = false;
        } else {
            widget.visible = true;
        }
    }

    protected void toggle_tree ()
    {
        toggle_visible_prototype (interface_tree_scroller);
    }

    protected void toggle_help ()
    {
        toggle_visible_prototype (interface_help_scroller);
    }

    protected void toggle_terminal ()
    {
        toggle_visible_prototype (interface_terminal_scroller);
    }

	protected Gtk.HeaderBar
	create_headerbar ()
	{
		headerbar = new HeaderBar ();
        headerbar.set_show_close_button(true);

        hide_tree = new ToggleButton ();
        hide_tree.image = new Gtk.Image.from_icon_name
            ("pane-hide-symbolic", IconSize.BUTTON);
        hide_tree.set_tooltip_text ("Hide tree");
        hide_tree.active = true;
        hide_tree.toggled.connect(toggle_tree);
        headerbar.pack_start (hide_tree);

        append_node = new Button.from_icon_name ("list-add-symbolic");
        append_node.set_tooltip_text ("Append new item to tree");
        headerbar.pack_start (append_node);

		file_box = new Box (Orientation.HORIZONTAL, 0);

		file_new = new Button.from_icon_name ("document-new-symbolic");
		file_new.set_tooltip_text ("New document");

		file_select =
			new FileChooserButton ("No file open", FileChooserAction.OPEN);
		file_select.set_tooltip_text ("Open document");

		file_export =
            new Button.from_icon_name ("document-export-symbolic");
		file_export.set_tooltip_text ("Export document");
		file_box.add (file_new);
		file_box.add (file_select);
		file_box.add (file_export);

		headerbar.set_custom_title (file_box);

		hide_help = new ToggleButton ();
        hide_help.image = new Gtk.Image.from_icon_name
            ("help-browser-symbolic", IconSize.BUTTON);
        hide_help.set_tooltip_text ("Open help browser");
        hide_help.toggled.connect (toggle_help);
		headerbar.pack_end (hide_help);

        hide_terminal = new ToggleButton ();
        hide_terminal.image = new Gtk.Image.from_icon_name
            ("utilities-terminal-symbolic", IconSize.BUTTON);
        hide_terminal.set_tooltip_text ("Pop up terminal");
        hide_terminal.toggled.connect (toggle_terminal);
        headerbar.pack_end (hide_terminal);

		redo = new Button.from_icon_name ("edit-redo-symbolic");
		redo.set_tooltip_text ("Redo");
		headerbar.pack_end (redo);

		undo = new Button.from_icon_name ("edit-undo-symbolic");
		undo.set_tooltip_text ("Undo");
		headerbar.pack_end (undo);

		return headerbar;
	}


	protected Gtk.Grid
    create_viewer ()
	{
		interface_grid = new Gtk.Grid ();

        interface_tree_scroller = new Gtk.ScrolledWindow (null, null);
        interface_tree_viewport = new Gtk.Viewport (null, null);
        interface_tree_scroller.add (interface_tree_viewport);

        interface_document_scroller = new Gtk.ScrolledWindow (null, null);
        interface_document_viewport = new Gtk.Viewport (null, null);
        interface_document_scroller.add (interface_document_viewport);

        interface_terminal_scroller = new Gtk.ScrolledWindow (null, null);
        interface_terminal_viewport = new Gtk.Viewport (null, null);
        interface_terminal_scroller.add (interface_terminal_viewport);

        interface_help_scroller = new Gtk.ScrolledWindow (null, null);
        interface_help_viewport = new Gtk.Viewport (null, null);
        interface_help_scroller.add (interface_help_viewport);

        interface_grid.attach (interface_tree_scroller,     0, 0, 1, 1);
        interface_grid.attach (interface_document_scroller, 1, 0, 1, 1);
        interface_grid.attach (interface_help_scroller,     2, 0, 1, 1);
        interface_grid.attach (interface_terminal_scroller, 0, 1, 3, 1);

        // just example placeholders to show the hide/show interface
        var temp_tree = new Gtk.Frame ("tree");
        temp_tree.expand = true;
        var temp_document = new Gtk.Frame ("document");
        temp_document.expand = true;
        var temp_terminal = new Gtk.Frame ("terminal");
        temp_terminal.expand = true;
        var temp_help = new Gtk.Frame ("help");
        temp_help.expand = true;

        interface_tree_viewport.add (temp_tree);
        interface_document_viewport.add (temp_document);
        interface_terminal_viewport.add (temp_terminal);
        interface_help_viewport.add (temp_help);

		return interface_grid;
	}

	public static int
	main (string[] args)
	{
		var app = new Incremental ();
		return app.run (args);
	}
}
