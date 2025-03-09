/*
windows: gcc -o main.exe main.c `pkg-config --cflags --libs gtk+-3.0` -mwindows
linux: gcc -o main main.c `pkg-config --cflags --libs gtk+-3.0`
*/

#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
int count = 0;
void show_message_dialog(GtkWidget *parent, GtkMessageType type, GtkButtonsType buttons, const char *message) {
  GtkWidget *dialog = gtk_message_dialog_new(
      GTK_WINDOW(parent),
      GTK_DIALOG_DESTROY_WITH_PARENT,
      type,
      buttons,
      "%s",
      message
  );
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

gboolean on_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_main_quit();
    return FALSE;
}

void plus_clicked(GtkWidget *widget, gpointer data) {

  GtkWidget *txt_cont_box = (GtkWidget *)data; // dataからtxt_cont_boxを取得

  GtkWidget* entry;
  char name[20];

  entry = gtk_entry_new();
  gtk_widget_show(entry);
  gtk_widget_set_can_focus(entry, TRUE);

  sprintf(name, "list%d", count);
  gtk_widget_set_name(entry, name);
  gtk_style_context_add_class(gtk_widget_get_style_context(entry), "txt_box");


  gtk_entry_set_text(GTK_ENTRY(entry), "文字打ってね....");

  gtk_widget_set_margin_start(entry, 80);
  gtk_widget_set_margin_end(entry, 80);

  gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);

  gtk_box_pack_start(GTK_BOX(txt_cont_box), entry, FALSE, FALSE, 0); // txt_cont_boxにentryを追加



}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "main.glade", NULL);

    // ウィンドウオブジェクトを取得
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));
    GtkWidget *label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    GtkWidget *plus = GTK_WIDGET(gtk_builder_get_object(builder, "plus"));
    GtkWidget *minus = GTK_WIDGET(gtk_builder_get_object(builder, "minus"));
    GtkWidget *txt_cont_box = GTK_WIDGET(gtk_builder_get_object(builder, "txt_cont_box"));
    

    gtk_widget_set_name(label1, "label1");
    gtk_widget_set_name(plus, "plus");

    gtk_style_context_add_class(gtk_widget_get_style_context(plus), "button_01");
    gtk_style_context_add_class(gtk_widget_get_style_context(minus), "button_01");




    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);

    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_window_set_default_size(GTK_WINDOW(window), 650, 350);
    gtk_widget_show_all(window);

    // "delete-event"シグナルを処理
    g_signal_connect(window, "delete-event", G_CALLBACK(on_delete_event), NULL);
    g_signal_connect(plus, "clicked", G_CALLBACK(plus_clicked), txt_cont_box);


    gtk_main();

    return 0;
}



