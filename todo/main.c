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
#include <windows.h>

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

  //plusが押されたとき

}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "main.glade", NULL);

    // ウィンドウオブジェクトを取得
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));
    GtkWidget *label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    GtkWidget *plus = GTK_WIDGET(gtk_builder_get_object(builder, "plus"));
    gtk_widget_set_name(label1, "label1");
    gtk_widget_set_name(plus, "plus");



    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);

    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_window_set_default_size(GTK_WINDOW(window), 650, 350);
    gtk_widget_show_all(window);

    // "delete-event"シグナルを処理
    g_signal_connect(window, "delete-event", G_CALLBACK(on_delete_event), NULL);
    g_signal_connect(plus, "clicked", G_CALLBACK(plus_clicked), NULL);


    gtk_main();

    return 0;
}

