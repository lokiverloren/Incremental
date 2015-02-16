/* Incremental.c generated by valac 0.27.1, the Vala compiler
 * generated from Incremental.vala, do not modify */

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

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define TYPE_INCREMENTAL (incremental_get_type ())
#define INCREMENTAL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_INCREMENTAL, Incremental))
#define INCREMENTAL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_INCREMENTAL, IncrementalClass))
#define IS_INCREMENTAL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_INCREMENTAL))
#define IS_INCREMENTAL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_INCREMENTAL))
#define INCREMENTAL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_INCREMENTAL, IncrementalClass))

typedef struct _Incremental Incremental;
typedef struct _IncrementalClass IncrementalClass;
typedef struct _IncrementalPrivate IncrementalPrivate;

#define INCREMENTAL_TYPE_SVP (incremental_svp_get_type ())
typedef struct _Incrementalsvp Incrementalsvp;

#define INCREMENTAL_TYPE_COLUMNS (incremental_columns_get_type ())
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

typedef void (*MyCallBack) (GAction* a, void* user_data);
struct _Incrementalsvp {
	GtkScrolledWindow* scroller;
	GtkViewport* viewport;
};

struct _Incremental {
	GtkApplication parent_instance;
	IncrementalPrivate * priv;
	gchar* AppName;
	gchar* Version;
	GtkApplicationWindow* window;
	GtkGrid* interface_grid;
	GtkTreeView* interface_tree_view;
	GtkHeaderBar* headerbar;
	GtkToggleButton* hide_tree;
	GtkButton* append_node;
	GtkBox* file_box;
	GtkButton* file_new;
	GtkFileChooserButton* file_select;
	GtkButton* file_export;
	GtkButton* undo;
	GtkButton* redo;
	GtkToggleButton* hide_terminal;
	GtkToggleButton* hide_help;
	GtkAccelGroup* accel_group;
	Incrementalsvp interface_tree;
	Incrementalsvp interface_document;
	Incrementalsvp interface_help;
	Incrementalsvp interface_terminal;
};

struct _IncrementalClass {
	GtkApplicationClass parent_class;
};

typedef enum  {
	INCREMENTAL_COLUMNS_HEAD,
	INCREMENTAL_COLUMNS_BODY,
	INCREMENTAL_COLUMNS_N_COLUMNS
} IncrementalColumns;


static gpointer incremental_parent_class = NULL;

GType incremental_get_type (void) G_GNUC_CONST;
GType incremental_svp_get_type (void) G_GNUC_CONST;
Incrementalsvp* incremental_svp_dup (const Incrementalsvp* self);
void incremental_svp_free (Incrementalsvp* self);
void incremental_svp_copy (const Incrementalsvp* self, Incrementalsvp* dest);
void incremental_svp_destroy (Incrementalsvp* self);
enum  {
	INCREMENTAL_DUMMY_PROPERTY
};
GType incremental_columns_get_type (void) G_GNUC_CONST;
Incremental* incremental_new (void);
Incremental* incremental_construct (GType object_type);
static void incremental_real_activate (GApplication* base);
GtkHeaderBar* incremental_create_headerbar (Incremental* self);
void incremental_create_actions (Incremental* self);
GtkGrid* incremental_create_viewer (Incremental* self);
void incremental_toggle_help (Incremental* self);
void incremental_toggle_terminal (Incremental* self);
void incremental_toggle_tree_activate (Incremental* self, GVariant* parameter);
void incremental_toggle_tree (Incremental* self);
void incremental_toggle_terminal_activate (Incremental* self, GVariant* parameter);
void incremental_toggle_help_activate (Incremental* self, GVariant* parameter);
static void _incremental_toggle_terminal_activate_g_simple_action_activate (GSimpleAction* _sender, GVariant* parameter, gpointer self);
static void _incremental_toggle_help_activate_g_simple_action_activate (GSimpleAction* _sender, GVariant* parameter, gpointer self);
static void _incremental_toggle_tree_activate_g_simple_action_activate (GSimpleAction* _sender, GVariant* parameter, gpointer self);
void incremental_toggle_visible_prototype (Incremental* self, GtkWidget* widget);
void incremental_new_svp (Incremental* self, Incrementalsvp* result);
gint incremental_main (gchar** args, int args_length1);
static void incremental_finalize (GObject* obj);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);


GType incremental_columns_get_type (void) {
	static volatile gsize incremental_columns_type_id__volatile = 0;
	if (g_once_init_enter (&incremental_columns_type_id__volatile)) {
		static const GEnumValue values[] = {{INCREMENTAL_COLUMNS_HEAD, "INCREMENTAL_COLUMNS_HEAD", "head"}, {INCREMENTAL_COLUMNS_BODY, "INCREMENTAL_COLUMNS_BODY", "body"}, {INCREMENTAL_COLUMNS_N_COLUMNS, "INCREMENTAL_COLUMNS_N_COLUMNS", "n-columns"}, {0, NULL, NULL}};
		GType incremental_columns_type_id;
		incremental_columns_type_id = g_enum_register_static ("IncrementalColumns", values);
		g_once_init_leave (&incremental_columns_type_id__volatile, incremental_columns_type_id);
	}
	return incremental_columns_type_id__volatile;
}


Incremental* incremental_construct (GType object_type) {
	Incremental * self = NULL;
	self = (Incremental*) g_object_new (object_type, "application-id", "org.agora.incremental", "flags", G_APPLICATION_FLAGS_NONE, NULL);
	return self;
}


Incremental* incremental_new (void) {
	return incremental_construct (TYPE_INCREMENTAL);
}


static const gchar* string_to_string (const gchar* self) {
	const gchar* result = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	result = self;
	return result;
}


static void incremental_real_activate (GApplication* base) {
	Incremental * self;
	GtkApplicationWindow* window = NULL;
	GtkApplicationWindow* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	GtkHeaderBar* _tmp7_ = NULL;
	GtkHeaderBar* _tmp8_ = NULL;
	GtkGrid* _tmp9_ = NULL;
	GtkGrid* _tmp10_ = NULL;
	self = (Incremental*) base;
	_tmp0_ = (GtkApplicationWindow*) gtk_application_window_new ((GtkApplication*) self);
	g_object_ref_sink (_tmp0_);
	window = _tmp0_;
	gtk_window_resize ((GtkWindow*) window, 800, 600);
	_tmp1_ = self->AppName;
	_tmp2_ = string_to_string (_tmp1_);
	_tmp3_ = self->Version;
	_tmp4_ = string_to_string (_tmp3_);
	_tmp5_ = g_strconcat (_tmp2_, " ", _tmp4_, NULL);
	_tmp6_ = _tmp5_;
	gtk_window_set_title ((GtkWindow*) window, _tmp6_);
	_g_free0 (_tmp6_);
	gtk_window_set_position ((GtkWindow*) window, GTK_WIN_POS_CENTER);
	_tmp7_ = incremental_create_headerbar (self);
	_tmp8_ = _tmp7_;
	gtk_window_set_titlebar ((GtkWindow*) window, (GtkWidget*) _tmp8_);
	_g_object_unref0 (_tmp8_);
	incremental_create_actions (self);
	_tmp9_ = incremental_create_viewer (self);
	_g_object_unref0 (self->interface_grid);
	self->interface_grid = _tmp9_;
	_tmp10_ = self->interface_grid;
	gtk_container_add ((GtkContainer*) window, (GtkWidget*) _tmp10_);
	gtk_widget_show_all ((GtkWidget*) window);
	incremental_toggle_help (self);
	incremental_toggle_terminal (self);
	_g_object_unref0 (window);
}


void incremental_toggle_tree_activate (Incremental* self, GVariant* parameter) {
	FILE* _tmp0_ = NULL;
	g_return_if_fail (self != NULL);
	incremental_toggle_tree (self);
	_tmp0_ = stderr;
	fprintf (_tmp0_, "toggle-tree action activated\n");
}


void incremental_toggle_terminal_activate (Incremental* self, GVariant* parameter) {
	FILE* _tmp0_ = NULL;
	g_return_if_fail (self != NULL);
	incremental_toggle_terminal (self);
	_tmp0_ = stderr;
	fprintf (_tmp0_, "toggle-terminal action activated\n");
}


void incremental_toggle_help_activate (Incremental* self, GVariant* parameter) {
	FILE* _tmp0_ = NULL;
	g_return_if_fail (self != NULL);
	incremental_toggle_help (self);
	_tmp0_ = stderr;
	fprintf (_tmp0_, "toggle-help action activated\n");
}


static void _incremental_toggle_terminal_activate_g_simple_action_activate (GSimpleAction* _sender, GVariant* parameter, gpointer self) {
	incremental_toggle_terminal_activate ((Incremental*) self, parameter);
}


static void _incremental_toggle_help_activate_g_simple_action_activate (GSimpleAction* _sender, GVariant* parameter, gpointer self) {
	incremental_toggle_help_activate ((Incremental*) self, parameter);
}


static void _incremental_toggle_tree_activate_g_simple_action_activate (GSimpleAction* _sender, GVariant* parameter, gpointer self) {
	incremental_toggle_tree_activate ((Incremental*) self, parameter);
}


void incremental_create_actions (Incremental* self) {
	GSimpleAction* toggle_terminal_action = NULL;
	GSimpleAction* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	gchar** _tmp2_ = NULL;
	gchar** _tmp3_ = NULL;
	gint _tmp3__length1 = 0;
	GSimpleAction* toggle_help_action = NULL;
	GSimpleAction* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	gchar** _tmp6_ = NULL;
	gchar** _tmp7_ = NULL;
	gint _tmp7__length1 = 0;
	GSimpleAction* toggle_tree_action = NULL;
	GSimpleAction* _tmp8_ = NULL;
	gchar* _tmp9_ = NULL;
	gchar** _tmp10_ = NULL;
	gchar** _tmp11_ = NULL;
	gint _tmp11__length1 = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = g_simple_action_new ("toggle-terminal", NULL);
	toggle_terminal_action = _tmp0_;
	g_signal_connect_object (toggle_terminal_action, "activate", (GCallback) _incremental_toggle_terminal_activate_g_simple_action_activate, self, 0);
	g_action_map_add_action ((GActionMap*) self, (GAction*) toggle_terminal_action);
	_tmp1_ = g_strdup ("F12");
	_tmp2_ = g_new0 (gchar*, 1 + 1);
	_tmp2_[0] = _tmp1_;
	_tmp3_ = _tmp2_;
	_tmp3__length1 = 1;
	gtk_application_set_accels_for_action ((GtkApplication*) self, "app.toggle-terminal", _tmp3_);
	_tmp3_ = (_vala_array_free (_tmp3_, _tmp3__length1, (GDestroyNotify) g_free), NULL);
	_tmp4_ = g_simple_action_new ("toggle-help", NULL);
	toggle_help_action = _tmp4_;
	g_signal_connect_object (toggle_help_action, "activate", (GCallback) _incremental_toggle_help_activate_g_simple_action_activate, self, 0);
	g_action_map_add_action ((GActionMap*) self, (GAction*) toggle_help_action);
	_tmp5_ = g_strdup ("F1");
	_tmp6_ = g_new0 (gchar*, 1 + 1);
	_tmp6_[0] = _tmp5_;
	_tmp7_ = _tmp6_;
	_tmp7__length1 = 1;
	gtk_application_set_accels_for_action ((GtkApplication*) self, "app.toggle-help", _tmp7_);
	_tmp7_ = (_vala_array_free (_tmp7_, _tmp7__length1, (GDestroyNotify) g_free), NULL);
	_tmp8_ = g_simple_action_new ("toggle-tree", NULL);
	toggle_tree_action = _tmp8_;
	g_signal_connect_object (toggle_tree_action, "activate", (GCallback) _incremental_toggle_tree_activate_g_simple_action_activate, self, 0);
	g_action_map_add_action ((GActionMap*) self, (GAction*) toggle_tree_action);
	_tmp9_ = g_strdup ("F10");
	_tmp10_ = g_new0 (gchar*, 1 + 1);
	_tmp10_[0] = _tmp9_;
	_tmp11_ = _tmp10_;
	_tmp11__length1 = 1;
	gtk_application_set_accels_for_action ((GtkApplication*) self, "app.toggle-tree", _tmp11_);
	_tmp11_ = (_vala_array_free (_tmp11_, _tmp11__length1, (GDestroyNotify) g_free), NULL);
	_g_object_unref0 (toggle_tree_action);
	_g_object_unref0 (toggle_help_action);
	_g_object_unref0 (toggle_terminal_action);
}


void incremental_toggle_visible_prototype (Incremental* self, GtkWidget* widget) {
	GtkWidget* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	g_return_if_fail (self != NULL);
	g_return_if_fail (widget != NULL);
	_tmp0_ = widget;
	_tmp1_ = gtk_widget_get_visible (_tmp0_);
	_tmp2_ = _tmp1_;
	if (_tmp2_) {
		GtkWidget* _tmp3_ = NULL;
		_tmp3_ = widget;
		gtk_widget_set_visible (_tmp3_, FALSE);
	} else {
		GtkWidget* _tmp4_ = NULL;
		_tmp4_ = widget;
		gtk_widget_set_visible (_tmp4_, TRUE);
	}
}


void incremental_toggle_tree (Incremental* self) {
	Incrementalsvp _tmp0_ = {0};
	GtkScrolledWindow* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->interface_tree;
	_tmp1_ = _tmp0_.scroller;
	incremental_toggle_visible_prototype (self, (GtkWidget*) _tmp1_);
}


void incremental_toggle_help (Incremental* self) {
	Incrementalsvp _tmp0_ = {0};
	GtkScrolledWindow* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->interface_help;
	_tmp1_ = _tmp0_.scroller;
	incremental_toggle_visible_prototype (self, (GtkWidget*) _tmp1_);
}


void incremental_toggle_terminal (Incremental* self) {
	Incrementalsvp _tmp0_ = {0};
	GtkScrolledWindow* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->interface_terminal;
	_tmp1_ = _tmp0_.scroller;
	incremental_toggle_visible_prototype (self, (GtkWidget*) _tmp1_);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


GtkHeaderBar* incremental_create_headerbar (Incremental* self) {
	GtkHeaderBar* result = NULL;
	GtkHeaderBar* _tmp0_ = NULL;
	GtkHeaderBar* _tmp1_ = NULL;
	GtkButton* _tmp2_ = NULL;
	GtkButton* _tmp3_ = NULL;
	GtkHeaderBar* _tmp4_ = NULL;
	GtkButton* _tmp5_ = NULL;
	GtkButton* _tmp6_ = NULL;
	GtkButton* _tmp7_ = NULL;
	GtkHeaderBar* _tmp8_ = NULL;
	GtkButton* _tmp9_ = NULL;
	GtkButton* _tmp10_ = NULL;
	GtkButton* _tmp11_ = NULL;
	GtkHeaderBar* _tmp12_ = NULL;
	GtkButton* _tmp13_ = NULL;
	GtkBox* _tmp14_ = NULL;
	GtkButton* _tmp15_ = NULL;
	GtkButton* _tmp16_ = NULL;
	GtkFileChooserButton* _tmp17_ = NULL;
	GtkFileChooserButton* _tmp18_ = NULL;
	GtkButton* _tmp19_ = NULL;
	GtkButton* _tmp20_ = NULL;
	GtkBox* _tmp21_ = NULL;
	GtkButton* _tmp22_ = NULL;
	GtkBox* _tmp23_ = NULL;
	GtkFileChooserButton* _tmp24_ = NULL;
	GtkBox* _tmp25_ = NULL;
	GtkButton* _tmp26_ = NULL;
	GtkHeaderBar* _tmp27_ = NULL;
	GtkBox* _tmp28_ = NULL;
	GtkToggleButton* _tmp29_ = NULL;
	GtkToggleButton* _tmp30_ = NULL;
	GtkImage* _tmp31_ = NULL;
	GtkImage* _tmp32_ = NULL;
	GtkToggleButton* _tmp33_ = NULL;
	GtkToggleButton* _tmp34_ = NULL;
	GtkHeaderBar* _tmp35_ = NULL;
	GtkToggleButton* _tmp36_ = NULL;
	GtkToggleButton* _tmp37_ = NULL;
	GtkToggleButton* _tmp38_ = NULL;
	GtkImage* _tmp39_ = NULL;
	GtkImage* _tmp40_ = NULL;
	GtkToggleButton* _tmp41_ = NULL;
	GtkToggleButton* _tmp42_ = NULL;
	GtkHeaderBar* _tmp43_ = NULL;
	GtkToggleButton* _tmp44_ = NULL;
	GtkToggleButton* _tmp45_ = NULL;
	GtkToggleButton* _tmp46_ = NULL;
	GtkImage* _tmp47_ = NULL;
	GtkImage* _tmp48_ = NULL;
	GtkToggleButton* _tmp49_ = NULL;
	GtkToggleButton* _tmp50_ = NULL;
	GtkToggleButton* _tmp51_ = NULL;
	GtkHeaderBar* _tmp52_ = NULL;
	GtkToggleButton* _tmp53_ = NULL;
	GtkHeaderBar* _tmp54_ = NULL;
	GtkHeaderBar* _tmp55_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = (GtkHeaderBar*) gtk_header_bar_new ();
	g_object_ref_sink (_tmp0_);
	_g_object_unref0 (self->headerbar);
	self->headerbar = _tmp0_;
	_tmp1_ = self->headerbar;
	gtk_header_bar_set_show_close_button (_tmp1_, TRUE);
	_tmp2_ = (GtkButton*) gtk_button_new_from_icon_name ("list-add-symbolic", GTK_ICON_SIZE_BUTTON);
	g_object_ref_sink (_tmp2_);
	_g_object_unref0 (self->append_node);
	self->append_node = _tmp2_;
	_tmp3_ = self->append_node;
	gtk_widget_set_tooltip_text ((GtkWidget*) _tmp3_, "Append new item to tree");
	_tmp4_ = self->headerbar;
	_tmp5_ = self->append_node;
	gtk_header_bar_pack_start (_tmp4_, (GtkWidget*) _tmp5_);
	_tmp6_ = (GtkButton*) gtk_button_new_from_icon_name ("edit-undo-symbolic", GTK_ICON_SIZE_BUTTON);
	g_object_ref_sink (_tmp6_);
	_g_object_unref0 (self->undo);
	self->undo = _tmp6_;
	_tmp7_ = self->undo;
	gtk_widget_set_tooltip_text ((GtkWidget*) _tmp7_, "Undo");
	_tmp8_ = self->headerbar;
	_tmp9_ = self->undo;
	gtk_header_bar_pack_start (_tmp8_, (GtkWidget*) _tmp9_);
	_tmp10_ = (GtkButton*) gtk_button_new_from_icon_name ("edit-redo-symbolic", GTK_ICON_SIZE_BUTTON);
	g_object_ref_sink (_tmp10_);
	_g_object_unref0 (self->redo);
	self->redo = _tmp10_;
	_tmp11_ = self->redo;
	gtk_widget_set_tooltip_text ((GtkWidget*) _tmp11_, "Redo");
	_tmp12_ = self->headerbar;
	_tmp13_ = self->redo;
	gtk_header_bar_pack_start (_tmp12_, (GtkWidget*) _tmp13_);
	_tmp14_ = (GtkBox*) gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	g_object_ref_sink (_tmp14_);
	_g_object_unref0 (self->file_box);
	self->file_box = _tmp14_;
	_tmp15_ = (GtkButton*) gtk_button_new_from_icon_name ("document-new-symbolic", GTK_ICON_SIZE_BUTTON);
	g_object_ref_sink (_tmp15_);
	_g_object_unref0 (self->file_new);
	self->file_new = _tmp15_;
	_tmp16_ = self->file_new;
	gtk_widget_set_tooltip_text ((GtkWidget*) _tmp16_, "New document");
	_tmp17_ = (GtkFileChooserButton*) gtk_file_chooser_button_new ("No file open", GTK_FILE_CHOOSER_ACTION_OPEN);
	g_object_ref_sink (_tmp17_);
	_g_object_unref0 (self->file_select);
	self->file_select = _tmp17_;
	_tmp18_ = self->file_select;
	gtk_widget_set_tooltip_text ((GtkWidget*) _tmp18_, "Open document");
	_tmp19_ = (GtkButton*) gtk_button_new_from_icon_name ("document-export-symbolic", GTK_ICON_SIZE_BUTTON);
	g_object_ref_sink (_tmp19_);
	_g_object_unref0 (self->file_export);
	self->file_export = _tmp19_;
	_tmp20_ = self->file_export;
	gtk_widget_set_tooltip_text ((GtkWidget*) _tmp20_, "Export document");
	_tmp21_ = self->file_box;
	_tmp22_ = self->file_new;
	gtk_container_add ((GtkContainer*) _tmp21_, (GtkWidget*) _tmp22_);
	_tmp23_ = self->file_box;
	_tmp24_ = self->file_select;
	gtk_container_add ((GtkContainer*) _tmp23_, (GtkWidget*) _tmp24_);
	_tmp25_ = self->file_box;
	_tmp26_ = self->file_export;
	gtk_container_add ((GtkContainer*) _tmp25_, (GtkWidget*) _tmp26_);
	_tmp27_ = self->headerbar;
	_tmp28_ = self->file_box;
	gtk_header_bar_set_custom_title (_tmp27_, (GtkWidget*) _tmp28_);
	_tmp29_ = (GtkToggleButton*) gtk_toggle_button_new ();
	g_object_ref_sink (_tmp29_);
	_g_object_unref0 (self->hide_help);
	self->hide_help = _tmp29_;
	_tmp30_ = self->hide_help;
	_tmp31_ = (GtkImage*) gtk_image_new_from_icon_name ("help-browser-symbolic", GTK_ICON_SIZE_BUTTON);
	g_object_ref_sink (_tmp31_);
	_tmp32_ = _tmp31_;
	gtk_button_set_image ((GtkButton*) _tmp30_, (GtkWidget*) _tmp32_);
	_g_object_unref0 (_tmp32_);
	_tmp33_ = self->hide_help;
	gtk_widget_set_tooltip_text ((GtkWidget*) _tmp33_, "Open help browser");
	_tmp34_ = self->hide_help;
	gtk_actionable_set_action_name ((GtkActionable*) _tmp34_, "app.toggle-help");
	_tmp35_ = self->headerbar;
	_tmp36_ = self->hide_help;
	gtk_header_bar_pack_end (_tmp35_, (GtkWidget*) _tmp36_);
	_tmp37_ = (GtkToggleButton*) gtk_toggle_button_new ();
	g_object_ref_sink (_tmp37_);
	_g_object_unref0 (self->hide_terminal);
	self->hide_terminal = _tmp37_;
	_tmp38_ = self->hide_terminal;
	_tmp39_ = (GtkImage*) gtk_image_new_from_icon_name ("utilities-terminal-symbolic", GTK_ICON_SIZE_BUTTON);
	g_object_ref_sink (_tmp39_);
	_tmp40_ = _tmp39_;
	gtk_button_set_image ((GtkButton*) _tmp38_, (GtkWidget*) _tmp40_);
	_g_object_unref0 (_tmp40_);
	_tmp41_ = self->hide_terminal;
	gtk_widget_set_tooltip_text ((GtkWidget*) _tmp41_, "Pop up terminal");
	_tmp42_ = self->hide_terminal;
	gtk_actionable_set_action_name ((GtkActionable*) _tmp42_, "app.toggle-terminal");
	_tmp43_ = self->headerbar;
	_tmp44_ = self->hide_terminal;
	gtk_header_bar_pack_end (_tmp43_, (GtkWidget*) _tmp44_);
	_tmp45_ = (GtkToggleButton*) gtk_toggle_button_new ();
	g_object_ref_sink (_tmp45_);
	_g_object_unref0 (self->hide_tree);
	self->hide_tree = _tmp45_;
	_tmp46_ = self->hide_tree;
	_tmp47_ = (GtkImage*) gtk_image_new_from_icon_name ("pane-hide-symbolic", GTK_ICON_SIZE_BUTTON);
	g_object_ref_sink (_tmp47_);
	_tmp48_ = _tmp47_;
	gtk_button_set_image ((GtkButton*) _tmp46_, (GtkWidget*) _tmp48_);
	_g_object_unref0 (_tmp48_);
	_tmp49_ = self->hide_tree;
	gtk_widget_set_tooltip_text ((GtkWidget*) _tmp49_, "Hide tree");
	_tmp50_ = self->hide_tree;
	gtk_toggle_button_set_active (_tmp50_, TRUE);
	_tmp51_ = self->hide_tree;
	gtk_actionable_set_action_name ((GtkActionable*) _tmp51_, "app.toggle-tree");
	_tmp52_ = self->headerbar;
	_tmp53_ = self->hide_tree;
	gtk_header_bar_pack_end (_tmp52_, (GtkWidget*) _tmp53_);
	_tmp54_ = self->headerbar;
	_tmp55_ = _g_object_ref0 (_tmp54_);
	result = _tmp55_;
	return result;
}


void incremental_new_svp (Incremental* self, Incrementalsvp* result) {
	Incrementalsvp temp = {0};
	GtkScrolledWindow* _tmp0_ = NULL;
	GtkViewport* _tmp1_ = NULL;
	Incrementalsvp _tmp2_ = {0};
	Incrementalsvp _tmp3_ = {0};
	GtkScrolledWindow* _tmp4_ = NULL;
	Incrementalsvp _tmp5_ = {0};
	GtkViewport* _tmp6_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = (GtkScrolledWindow*) gtk_scrolled_window_new (NULL, NULL);
	g_object_ref_sink (_tmp0_);
	_tmp1_ = (GtkViewport*) gtk_viewport_new (NULL, NULL);
	g_object_ref_sink (_tmp1_);
	_g_object_unref0 (_tmp2_.scroller);
	_tmp2_.scroller = _tmp0_;
	_g_object_unref0 (_tmp2_.viewport);
	_tmp2_.viewport = _tmp1_;
	temp = _tmp2_;
	_tmp3_ = temp;
	_tmp4_ = _tmp3_.scroller;
	_tmp5_ = temp;
	_tmp6_ = _tmp5_.viewport;
	gtk_container_add ((GtkContainer*) _tmp4_, (GtkWidget*) _tmp6_);
	*result = temp;
	return;
}


GtkGrid* incremental_create_viewer (Incremental* self) {
	GtkGrid* result = NULL;
	GtkGrid* _tmp0_ = NULL;
	Incrementalsvp _tmp1_ = {0};
	Incrementalsvp _tmp2_ = {0};
	Incrementalsvp _tmp3_ = {0};
	Incrementalsvp _tmp4_ = {0};
	GtkGrid* _tmp5_ = NULL;
	Incrementalsvp _tmp6_ = {0};
	GtkScrolledWindow* _tmp7_ = NULL;
	GtkGrid* _tmp8_ = NULL;
	Incrementalsvp _tmp9_ = {0};
	GtkScrolledWindow* _tmp10_ = NULL;
	GtkGrid* _tmp11_ = NULL;
	Incrementalsvp _tmp12_ = {0};
	GtkScrolledWindow* _tmp13_ = NULL;
	GtkGrid* _tmp14_ = NULL;
	Incrementalsvp _tmp15_ = {0};
	GtkScrolledWindow* _tmp16_ = NULL;
	GtkFrame* temp_tree = NULL;
	GtkFrame* _tmp17_ = NULL;
	GtkFrame* temp_document = NULL;
	GtkFrame* _tmp18_ = NULL;
	GtkFrame* temp_terminal = NULL;
	GtkFrame* _tmp19_ = NULL;
	GtkFrame* temp_help = NULL;
	GtkFrame* _tmp20_ = NULL;
	Incrementalsvp _tmp21_ = {0};
	GtkViewport* _tmp22_ = NULL;
	Incrementalsvp _tmp23_ = {0};
	GtkViewport* _tmp24_ = NULL;
	Incrementalsvp _tmp25_ = {0};
	GtkViewport* _tmp26_ = NULL;
	Incrementalsvp _tmp27_ = {0};
	GtkViewport* _tmp28_ = NULL;
	GtkGrid* _tmp29_ = NULL;
	GtkGrid* _tmp30_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = (GtkGrid*) gtk_grid_new ();
	g_object_ref_sink (_tmp0_);
	_g_object_unref0 (self->interface_grid);
	self->interface_grid = _tmp0_;
	incremental_new_svp (self, &_tmp1_);
	incremental_svp_destroy (&self->interface_tree);
	self->interface_tree = _tmp1_;
	incremental_new_svp (self, &_tmp2_);
	incremental_svp_destroy (&self->interface_document);
	self->interface_document = _tmp2_;
	incremental_new_svp (self, &_tmp3_);
	incremental_svp_destroy (&self->interface_terminal);
	self->interface_terminal = _tmp3_;
	incremental_new_svp (self, &_tmp4_);
	incremental_svp_destroy (&self->interface_help);
	self->interface_help = _tmp4_;
	_tmp5_ = self->interface_grid;
	_tmp6_ = self->interface_tree;
	_tmp7_ = _tmp6_.scroller;
	gtk_grid_attach (_tmp5_, (GtkWidget*) _tmp7_, 0, 0, 1, 1);
	_tmp8_ = self->interface_grid;
	_tmp9_ = self->interface_document;
	_tmp10_ = _tmp9_.scroller;
	gtk_grid_attach (_tmp8_, (GtkWidget*) _tmp10_, 1, 0, 1, 1);
	_tmp11_ = self->interface_grid;
	_tmp12_ = self->interface_help;
	_tmp13_ = _tmp12_.scroller;
	gtk_grid_attach (_tmp11_, (GtkWidget*) _tmp13_, 2, 0, 1, 1);
	_tmp14_ = self->interface_grid;
	_tmp15_ = self->interface_terminal;
	_tmp16_ = _tmp15_.scroller;
	gtk_grid_attach (_tmp14_, (GtkWidget*) _tmp16_, 0, 1, 3, 1);
	_tmp17_ = (GtkFrame*) gtk_frame_new ("tree");
	g_object_ref_sink (_tmp17_);
	temp_tree = _tmp17_;
	g_object_set ((GtkWidget*) temp_tree, "expand", TRUE, NULL);
	_tmp18_ = (GtkFrame*) gtk_frame_new ("document");
	g_object_ref_sink (_tmp18_);
	temp_document = _tmp18_;
	g_object_set ((GtkWidget*) temp_document, "expand", TRUE, NULL);
	_tmp19_ = (GtkFrame*) gtk_frame_new ("terminal");
	g_object_ref_sink (_tmp19_);
	temp_terminal = _tmp19_;
	g_object_set ((GtkWidget*) temp_terminal, "expand", TRUE, NULL);
	_tmp20_ = (GtkFrame*) gtk_frame_new ("help");
	g_object_ref_sink (_tmp20_);
	temp_help = _tmp20_;
	g_object_set ((GtkWidget*) temp_help, "expand", TRUE, NULL);
	_tmp21_ = self->interface_tree;
	_tmp22_ = _tmp21_.viewport;
	gtk_container_add ((GtkContainer*) _tmp22_, (GtkWidget*) temp_tree);
	_tmp23_ = self->interface_document;
	_tmp24_ = _tmp23_.viewport;
	gtk_container_add ((GtkContainer*) _tmp24_, (GtkWidget*) temp_document);
	_tmp25_ = self->interface_terminal;
	_tmp26_ = _tmp25_.viewport;
	gtk_container_add ((GtkContainer*) _tmp26_, (GtkWidget*) temp_terminal);
	_tmp27_ = self->interface_help;
	_tmp28_ = _tmp27_.viewport;
	gtk_container_add ((GtkContainer*) _tmp28_, (GtkWidget*) temp_help);
	_tmp29_ = self->interface_grid;
	_tmp30_ = _g_object_ref0 (_tmp29_);
	result = _tmp30_;
	_g_object_unref0 (temp_help);
	_g_object_unref0 (temp_terminal);
	_g_object_unref0 (temp_document);
	_g_object_unref0 (temp_tree);
	return result;
}


gint incremental_main (gchar** args, int args_length1) {
	gint result = 0;
	Incremental* app = NULL;
	Incremental* _tmp0_ = NULL;
	gchar** _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
	gint _tmp2_ = 0;
	_tmp0_ = incremental_new ();
	app = _tmp0_;
	_tmp1_ = args;
	_tmp1__length1 = args_length1;
	_tmp2_ = g_application_run ((GApplication*) app, _tmp1__length1, _tmp1_);
	result = _tmp2_;
	_g_object_unref0 (app);
	return result;
}


int main (int argc, char ** argv) {
#if !GLIB_CHECK_VERSION (2,35,0)
	g_type_init ();
#endif
	return incremental_main (argv, argc);
}


void incremental_svp_copy (const Incrementalsvp* self, Incrementalsvp* dest) {
	GtkScrolledWindow* _tmp0_ = NULL;
	GtkScrolledWindow* _tmp1_ = NULL;
	GtkViewport* _tmp2_ = NULL;
	GtkViewport* _tmp3_ = NULL;
	_tmp0_ = (*self).scroller;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 ((*dest).scroller);
	(*dest).scroller = _tmp1_;
	_tmp2_ = (*self).viewport;
	_tmp3_ = _g_object_ref0 (_tmp2_);
	_g_object_unref0 ((*dest).viewport);
	(*dest).viewport = _tmp3_;
}


void incremental_svp_destroy (Incrementalsvp* self) {
	_g_object_unref0 ((*self).scroller);
	_g_object_unref0 ((*self).viewport);
}


Incrementalsvp* incremental_svp_dup (const Incrementalsvp* self) {
	Incrementalsvp* dup;
	dup = g_new0 (Incrementalsvp, 1);
	incremental_svp_copy (self, dup);
	return dup;
}


void incremental_svp_free (Incrementalsvp* self) {
	incremental_svp_destroy (self);
	g_free (self);
}


GType incremental_svp_get_type (void) {
	static volatile gsize incremental_svp_type_id__volatile = 0;
	if (g_once_init_enter (&incremental_svp_type_id__volatile)) {
		GType incremental_svp_type_id;
		incremental_svp_type_id = g_boxed_type_register_static ("Incrementalsvp", (GBoxedCopyFunc) incremental_svp_dup, (GBoxedFreeFunc) incremental_svp_free);
		g_once_init_leave (&incremental_svp_type_id__volatile, incremental_svp_type_id);
	}
	return incremental_svp_type_id__volatile;
}


static void incremental_class_init (IncrementalClass * klass) {
	incremental_parent_class = g_type_class_peek_parent (klass);
	((GApplicationClass *) klass)->activate = incremental_real_activate;
	G_OBJECT_CLASS (klass)->finalize = incremental_finalize;
}


static void incremental_instance_init (Incremental * self) {
	gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	_tmp0_ = g_strdup ("Incremental");
	self->AppName = _tmp0_;
	_tmp1_ = g_strdup ("0.1");
	self->Version = _tmp1_;
}


static void incremental_finalize (GObject* obj) {
	Incremental * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_INCREMENTAL, Incremental);
	_g_free0 (self->AppName);
	_g_free0 (self->Version);
	_g_object_unref0 (self->window);
	_g_object_unref0 (self->interface_grid);
	_g_object_unref0 (self->interface_tree_view);
	_g_object_unref0 (self->headerbar);
	_g_object_unref0 (self->hide_tree);
	_g_object_unref0 (self->append_node);
	_g_object_unref0 (self->file_box);
	_g_object_unref0 (self->file_new);
	_g_object_unref0 (self->file_select);
	_g_object_unref0 (self->file_export);
	_g_object_unref0 (self->undo);
	_g_object_unref0 (self->redo);
	_g_object_unref0 (self->hide_terminal);
	_g_object_unref0 (self->hide_help);
	_g_object_unref0 (self->accel_group);
	incremental_svp_destroy (&self->interface_tree);
	incremental_svp_destroy (&self->interface_document);
	incremental_svp_destroy (&self->interface_help);
	incremental_svp_destroy (&self->interface_terminal);
	G_OBJECT_CLASS (incremental_parent_class)->finalize (obj);
}


GType incremental_get_type (void) {
	static volatile gsize incremental_type_id__volatile = 0;
	if (g_once_init_enter (&incremental_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (IncrementalClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) incremental_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Incremental), 0, (GInstanceInitFunc) incremental_instance_init, NULL };
		GType incremental_type_id;
		incremental_type_id = g_type_register_static (gtk_application_get_type (), "Incremental", &g_define_type_info, 0);
		g_once_init_leave (&incremental_type_id__volatile, incremental_type_id);
	}
	return incremental_type_id__volatile;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}



