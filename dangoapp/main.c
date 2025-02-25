/*
gcc -o main main.c `pkg-config --cflags --libs gtk+-3.0`
*/
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
int num = 0;
int samyu = 0;
int width = 0;
int height = 0;
void open_url_in_browser(const char *url) {
    gchar *command = g_strdup_printf("xdg-open %s", url);
    GError *error = NULL;

    if (!g_spawn_command_line_async(command, &error)) {
        g_printerr("Failed to open URL: %s\n", error->message);
        g_error_free(error);
    }

    g_free(command);
}

void open_site_clicked(GtkWidget *widget, gpointer data) {
    const char *url = "https://umaidango.github.io/me/";
    open_url_in_browser(url);
}


void change_label(GtkWidget *time_label) {

    char str[100];

    snprintf(str, sizeof(str), "%d", num);

    printf("文字列: %s\n", str);

    gtk_label_set_text(GTK_LABEL(time_label), str); // time_label を GtkLabel * にキャスト

}


void inport_s(GtkWidget *time_label) {
  change_label(time_label);
}

void count_clicked(GtkWidget *widget, gpointer data) {
  num += 1;
  inport_s(GTK_WIDGET(data)); // data を GtkWidget * にキャストして inport_s を呼び出す
}

void async_count(GtkWidget *time_label, gpointer data) {
  num++;
  inport_s(GTK_WIDGET(data)); //dataをtime_labelにキャストして、inport_sを呼び出す（？）他の言語はそんなことしなくてもいいのに。。
}


void *thread_function(void *arg) {
  GtkWidget *time_label = (GtkWidget *)arg;
  struct timespec req, rem; // nanosleep 用の timespec 構造体

  req.tv_sec = 0;
  req.tv_nsec = 100000000L; // 0.1 秒 (100 ミリ秒 = 100,000,000 ナノ秒)
  
  while (1) {
    gpointer data = time_label; // data を time_label で初期化
    async_count(time_label, data);
    nanosleep(&req, NULL); // nanosleep で 0.1 秒スリープ
  }
  return NULL; //なくてもいいらしいけどあったほうがいいって（？）
}




int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "main.glade", NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));
    GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    GtkWidget *label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    GtkWidget *ud_img = GTK_WIDGET(gtk_builder_get_object(builder, "ud_img"));
    GtkWidget *grid_name = GTK_WIDGET(gtk_builder_get_object(builder, "grid_name"));
    GtkWidget *open_site = GTK_WIDGET(gtk_builder_get_object(builder, "open_site"));
    GtkWidget *box_01 = GTK_WIDGET(gtk_builder_get_object(builder, "box_01"));
    GtkWidget *time_label = GTK_WIDGET(gtk_builder_get_object(builder, "time"));
    GtkWidget *win_size_label = GTK_WIDGET(gtk_builder_get_object(builder, "win_size_label"));
    GtkWidget *count_btn = GTK_WIDGET(gtk_builder_get_object(builder, "count"));
    gtk_widget_set_name(label, "label1");
    gtk_widget_set_name(ud_img, "ud_img");
    gtk_widget_set_name(grid_name, "grid_name");
    gtk_widget_set_name(open_site, "open_site");
    gtk_widget_set_name(box_01, "box_01");
    gtk_widget_set_name(box_01, "box_01");
    gtk_widget_set_name(time_label, "time_label");
    gtk_widget_set_name(count_btn, "count_btn");
    gtk_widget_set_name(win_size_label, "win_size_label");
    
    GdkPixbuf *original_pixbuf = gdk_pixbuf_new_from_file("image.png", NULL);
    if (original_pixbuf != NULL) {
        GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(original_pixbuf, 85, 85, GDK_INTERP_BILINEAR);
        if (scaled_pixbuf != NULL) {
            gtk_image_set_from_pixbuf(GTK_IMAGE(ud_img), scaled_pixbuf);
            g_object_unref(scaled_pixbuf);
        } else {
            g_print("Failed to scale pixbuf\n");
        }
        g_object_unref(original_pixbuf);
    } else {
        g_print("Failed to load image: image.png\n");
    }

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);

    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_set_default_size(GTK_WINDOW(window), 650, 350);
    gtk_widget_show_all(window);
    g_signal_connect(open_site, "clicked", G_CALLBACK(open_site_clicked), NULL);
    g_signal_connect(count_btn, "clicked", G_CALLBACK(count_clicked), time_label);
    change_label(time_label);
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, (void *)time_label); // スレッドを作成し、time_label を渡す

    gtk_main();
    
    return 0;
}