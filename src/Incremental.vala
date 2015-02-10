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
	protected Gtk.FileChooserButton file_button;
	protected Gtk.Button terminal_button;

	public string AppName = "Incremental";
	public string Version = "0.1" ;

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
		window.add(create_interface ());
		window.show_all ();
	}
	
	protected HeaderBar
	create_headerbar ()
	{
		var headerbar = new HeaderBar ();

		var file_box = new Box (Orientation.HORIZONTAL, 0);
		var file_new = new Button.from_icon_name ("document-new-symbolic");
		file_new.set_tooltip_text ("New document");

		file_button =
			new FileChooserButton ("No file open", FileChooserAction.OPEN);
		file_button.set_tooltip_text ("Open document");

		var file_export =
			new Button.from_icon_name ("document-export-symbolic");
		file_export.set_tooltip_text ("Export document");
		file_box.add (file_new);
		file_box.add (file_button);
		file_box.add (file_export);

		headerbar.set_custom_title (file_box);
		headerbar.set_show_close_button(true);

		var hide_tree = new Button.from_icon_name ("pane-hide-symbolic");
		hide_tree.set_tooltip_text ("Hide tree");
		headerbar.pack_start (hide_tree);

		var tree_append = new Button.from_icon_name ("list-add-symbolic");
		tree_append.set_tooltip_text ("Append new item to tree");
		headerbar.pack_start (tree_append);

		terminal_button =
			new Button.from_icon_name ("utilities-terminal-symbolic");
		terminal_button.set_tooltip_text ("Pop up terminal");
		headerbar.pack_end (terminal_button);

		var redo_button = new Button.from_icon_name ("edit-redo-symbolic");
		redo_button.set_tooltip_text ("Redo");
		headerbar.pack_end (redo_button);

		var undo_button = new Button.from_icon_name ("edit-undo-symbolic");
		undo_button.set_tooltip_text ("Undo");
		headerbar.pack_end (undo_button);

		return headerbar;
	}	

	protected Gtk.TreeView create_treeview ()
	{
		var treeview = new Gtk.TreeView (); 
		return treeview;
	}
	
	protected Gtk.Grid create_interface ()
	{
		var grid = new Gtk.Grid ();
		
		return grid;
	}

	public static int
	main (string[] args) 
	{
		var app = new Incremental ();
		return app.run (args);
	}
}
