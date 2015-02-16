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
using GLib;

public delegate void MyCallBack(GLib.Action a);

public class
Incremental : Gtk.Application
{
    // Application name stuff
	public string AppName = "Incremental";
	public string Version = "0.1" ;

    // GUI interface objects
	protected Gtk.ApplicationWindow window;

    protected Gtk.Grid interface_grid;

    protected Gtk.TreeView interface_tree_view;

    // headerbar interface elements
    protected Gtk.HeaderBar headerbar;

    protected Gtk.ToggleButton hide_tree;
    protected string hide_tree_accelerator = "F10";
    protected string hide_tree_tip = "Toggle visibility of tree";
    protected Gtk.Button append_node;
    protected string append_node_accelerator = "<ctrl><shift>n";
    protected string append_node_tip = "Append new node to tree";

    protected Gtk.Box file_box;
    protected Gtk.Button file_new;
    protected string file_new_accelerator = "<ctrl>n";
    protected string file_new_tip = "Create new empty document";
    protected Gtk.FileChooserButton file_select;
    protected Gtk.Button file_export;
    protected string file_export_accelerator = "<ctrl>e";
    protected string file_export_tip = "Export to other format";

    protected Gtk.Button undo;
    protected string undo_accelerator = "<ctrl>z";
    protected string undo_tip = "Undo last change";
    protected Gtk.Button redo;
    protected string redo_accelerator = "<ctrl>y";
    protected string redo_tip = "Redo last undone change";
    protected Gtk.ToggleButton hide_terminal;
    protected string hide_terminal_accelerator = "F12";
    protected string hide_terminal_tip = "Toggle visibility of terminal";
    protected Gtk.ToggleButton hide_help;
    protected string hide_help_accelerator = "F1";
    protected string hide_help_tip = "Toggle visibility of help browser";

	public enum
	Columns
	{
		HEAD,
		BODY,
		N_COLUMNS
	}

	public struct
	svp
	{
		Gtk.ScrolledWindow scroller;
		Gtk.Viewport viewport;
	}

	protected svp interface_tree;
	protected svp interface_document;
	protected svp interface_help;
	protected svp interface_terminal;

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

		create_actions ();

        interface_grid = create_viewer ();

		window.add(interface_grid);

		window.show_all ();
        toggle_help();
        toggle_terminal();
	}

	protected void
	create_actions ()
	{
		var toggle_terminal_action = 
			new GLib.SimpleAction.stateful ("toggle-terminal", null,
				new Variant.boolean (false));
		toggle_terminal_action.activate.connect (()=>{
	    	this.hold ();
	    	Variant state = toggle_terminal_action.get_state ();
	    	bool b = state.get_boolean ();
	    	toggle_terminal_action.set_state (new Variant.boolean (!b));
    	    toggle_visible_prototype (interface_terminal.scroller);
			this.release ();
			});
		this.add_action (toggle_terminal_action);
		this.set_accels_for_action ("app.toggle-terminal", {"F12"});

		var toggle_help_action = 
			new GLib.SimpleAction.stateful ("toggle-help", null,
				new Variant.boolean (false));
		toggle_help_action.activate.connect (()=> {
	    	this.hold ();
	    	Variant state = toggle_help_action.get_state();
	    	bool b = state.get_boolean ();
	    	toggle_help_action.set_state (new Variant.boolean (!b));
    	    toggle_visible_prototype (interface_help.scroller);
			this.release ();
			});
		this.add_action (toggle_help_action);
		this.set_accels_for_action ("app.toggle-help", {"F1"});

		var toggle_tree_action = 
			new GLib.SimpleAction.stateful ("toggle-tree", null,
				new Variant.boolean (true));
		toggle_tree_action.activate.connect (()=> {
	    	this.hold ();
	    	Variant state = toggle_tree_action.get_state();
	    	bool b = state.get_boolean ();
	    	toggle_tree_action.set_state (new Variant.boolean (!b));
    	    toggle_visible_prototype (interface_tree.scroller);
			this.release ();
			});
		this.add_action (toggle_tree_action);
		this.set_accels_for_action ("app.toggle-tree", {"F10"});

		var undo_action = 
			new GLib.SimpleAction ("undo", null);
		undo_action.activate.connect (()=> {
	    	this.hold ();
	    	stderr.printf ("user clicked undo or pressed <ctrl>z\n");
			this.release ();
			});
		this.add_action (undo_action);
		this.set_accels_for_action ("app.undo", {undo_accelerator});

		var redo_action = 
			new GLib.SimpleAction ("redo", null);
		redo_action.activate.connect (()=> {
	    	this.hold ();
	    	stderr.printf ("user clicked redo or pressed <ctrl>y\n");
			this.release ();
			});
		this.add_action (redo_action);
		this.set_accels_for_action ("app.redo", {"<ctrl>y"});

		var append_action = 
			new GLib.SimpleAction ("append", null);
		append_action.activate.connect (()=> {
	    	this.hold ();
	    	stderr.printf ("user clicked append node or pressed <ctrl><shift>n\n");
			this.release ();
			});
		this.add_action (append_action);
		this.set_accels_for_action ("app.append", {"<ctrl><shift>n"});

		var new_action = 
			new GLib.SimpleAction ("new", null);
		new_action.activate.connect (()=> {
	    	this.hold ();
	    	stderr.printf ("user clicked new or pressed <ctrl>n\n");
			this.release ();
			});
		this.add_action (new_action);
		this.set_accels_for_action ("app.new", {"<ctrl>n"});

		var export_action = 
			new GLib.SimpleAction ("export", null);
		export_action.activate.connect (()=> {
	    	this.hold ();
	    	stderr.printf ("user clicked export or pressed <ctrl>e\n");
			this.release ();
			});
		this.add_action (export_action);
		this.set_accels_for_action ("app.export", {"<ctrl>e"});
	}

    protected void
	toggle_visible_prototype (Gtk.Widget widget)
    {
        if (widget.visible)
        {
            widget.visible = false;
        } else {
            widget.visible = true;
        }
    }

    protected void
	toggle_tree ()
    {

    }

    protected void
	toggle_help ()
    {
        toggle_visible_prototype (interface_help.scroller);
    }

    protected void
	toggle_terminal ()
    {
        toggle_visible_prototype (interface_terminal.scroller);
    }

    protected string create_tip_with_accel (string tip, string accel)
    {
    	string accel_tip;
    	uint accel_key;
    	Gdk.ModifierType accel_mods;
    	Gtk.accelerator_parse (accel, out accel_key, out accel_mods);
    	accel_tip = "\n<b>(" + Gtk.accelerator_get_label (accel_key, accel_mods) +
    		")</b>";
    	return tip + accel_tip;
    }

	protected Gtk.HeaderBar
	create_headerbar ()
	{
		headerbar = new HeaderBar ();
        headerbar.set_show_close_button(true);

        append_node = new Button.from_icon_name ("list-add-symbolic");
        append_node.set_tooltip_markup (create_tip_with_accel (append_node_tip,
        	append_node_accelerator));
        append_node.set_action_name ("app.append");
        headerbar.pack_start (append_node);

		undo = new Button.from_icon_name ("edit-undo-symbolic");
        undo.set_tooltip_markup (create_tip_with_accel (undo_tip,
        	undo_accelerator));
        undo.set_action_name ("app.undo");
		headerbar.pack_start (undo);

		redo = new Button.from_icon_name ("edit-redo-symbolic");
        redo.set_tooltip_markup (create_tip_with_accel (redo_tip,
        	redo_accelerator));
        redo.set_action_name ("app.redo");
		headerbar.pack_start (redo);

		file_box = new Box (Orientation.HORIZONTAL, 0);

		file_new = new Button.from_icon_name ("document-new-symbolic");
        file_new.set_tooltip_markup (create_tip_with_accel (file_new_tip,
        	file_new_accelerator));
		file_new.set_action_name ("app.new");

		file_select =
			new FileChooserButton ("No file open", FileChooserAction.OPEN);
		file_select.set_tooltip_text ("Open document");

		file_export =
            new Button.from_icon_name ("document-export-symbolic");
        file_export.set_tooltip_markup (create_tip_with_accel (file_export_tip,
        	file_export_accelerator));
		file_export.set_action_name ("app.export");

		file_box.add (file_new);
		file_box.add (file_select);
		file_box.add (file_export);

		headerbar.set_custom_title (file_box);

		hide_help = new ToggleButton ();
        hide_help.image = new Gtk.Image.from_icon_name
            ("help-browser-symbolic", IconSize.BUTTON);
        hide_help.set_tooltip_markup (create_tip_with_accel (hide_help_tip,
        	hide_help_accelerator));
        //hide_help.toggled.connect (toggle_help);
        hide_help.set_action_name ("app.toggle-help");
		headerbar.pack_end (hide_help);

        hide_terminal = new ToggleButton ();
        hide_terminal.image = new Gtk.Image.from_icon_name
            ("utilities-terminal-symbolic", IconSize.BUTTON);
        hide_terminal.set_tooltip_markup (create_tip_with_accel (hide_terminal_tip,
        	hide_terminal_accelerator));
        //hide_terminal.toggled.connect (toggle_terminal);
        hide_terminal.set_action_name ("app.toggle-terminal");
        headerbar.pack_end (hide_terminal);

        hide_tree = new ToggleButton ();
        hide_tree.image = new Gtk.Image.from_icon_name
            ("pane-hide-symbolic", IconSize.BUTTON);
        hide_tree.set_tooltip_markup (create_tip_with_accel (hide_tree_tip,
        	hide_tree_accelerator));
    	hide_tree.active = true;
        //hide_tree.toggled.connect(toggle_tree);
        hide_tree.set_action_name ("app.toggle-tree");
        headerbar.pack_end (hide_tree);

		return headerbar;
	}

	protected svp
	new_svp ()
	{
		svp temp = {
			new Gtk.ScrolledWindow (null, null),
			new Gtk.Viewport (null, null)
		};
		temp.scroller.add (temp.viewport);
		return temp;
	}

	protected Gtk.Grid
    create_viewer ()
	{
		interface_grid = new Gtk.Grid ();

        interface_tree = new_svp ();
        interface_document = new_svp ();
        interface_terminal = new_svp ();
        interface_help = new_svp ();

        interface_grid.attach (interface_tree.scroller,     0, 0, 1, 1);
        interface_grid.attach (interface_document.scroller, 1, 0, 1, 1);
        interface_grid.attach (interface_help.scroller,     2, 0, 1, 1);
        interface_grid.attach (interface_terminal.scroller, 0, 1, 3, 1);

        // placeholders to show the hide/show interface
        var temp_tree = new Gtk.Frame ("tree");
        temp_tree.expand = true;
        var temp_document = new Gtk.Frame ("document");
        temp_document.expand = true;
        var temp_terminal = new Gtk.Frame ("terminal");
        temp_terminal.expand = true;
        var temp_help = new Gtk.Frame ("help");
        temp_help.expand = true;

        interface_tree.viewport.add (temp_tree);
        interface_document.viewport.add (temp_document);
        interface_terminal.viewport.add (temp_terminal);
        interface_help.viewport.add (temp_help);

		return interface_grid;
	}

	public static int
	main (string[] args)
	{
		var app = new Incremental ();
		return app.run (args);
	}
}
