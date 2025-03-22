/*
gcc -o main main.c `pkg-config --cflags --libs gtk+-3.0`
*/
//なんて素敵なコード❤、Cでこれは流石！
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
char text[100];

void on_window_destroy(GtkWidget *widget, gpointer data) {
  gtk_main_quit();
}

void plus_1(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "1");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);
}

void on_entry_changed(GtkEntry *entry, gpointer user_data) {
  const char *entry_txt = gtk_entry_get_text(entry);
  strncpy(text, entry_txt, sizeof(text) - 1);
  text[sizeof(text) - 1] = '\0'; 
}

void plus_2(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "2");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);
}

void plus_3(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "3");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);
}

void plus_4(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "4");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);
}

void plus_5(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "5");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);
}

void plus_6(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "6");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);
}

void plus_7(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "7");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);
}

void plus_8(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "8");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);  
}

void plus_9(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "9");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);  
}

void plus_0(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "0");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);  
}

void minus_plus(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "-");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);  
}

void plus_plus(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "+");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);  
}

void kakeru_plus(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "*");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);  
}

void waru_plus(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), "/");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);  
}

void dot_plus(GtkWidget *button, gpointer calc_textbox) {
  snprintf(text + strlen(text), sizeof(text) - strlen(text), ".");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);  
}


void delete_box(GtkWidget *button, gpointer calc_textbox) {

  strcpy(text, "");
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);  
}

void format_double(double value, char *result) {
  char temp[100];
  sprintf(temp, "%lf", value);

  int len = strlen(temp);
  int i;
  for (i = len - 1; i >= 0; i--) {
      if (temp[i] == '0') {
          temp[i] = '\0';
      } else if (temp[i] == '.') {
          temp[i] = '\0';
          break;
      } else {
          break;
      }
  }
  strcpy(result, temp);
}


void kotae_plus(GtkWidget *button, gpointer calc_textbox) {
  double num1, num2, result;
  char operator;
  char temp[100];


  if (sscanf(text, "%lf %c %lf", &num1, &operator, &num2) == 3) {

    printf("num1: %lf\n", num1);

    printf("operator: %c\n", operator);

    printf("num2: %lf\n", num2);

}
  // 計算
  switch (operator) {
      case '+':
          result = num1 + num2;
          break;
      case '-':
          result = num1 - num2;
          break;
      case '*':
          result = num1 * num2;
          break;
      case '/':
          result = num1 / num2;
          break;
      default:
          result = atoi(text);
  }

  
  // 結果を文字列に変換
  sprintf(temp, "%g", result);

  // 元の配列に結果をコピー
  strcpy(text, temp);
  gtk_entry_set_text(GTK_ENTRY(calc_textbox), text);  


}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    GtkBuilder *builder = gtk_builder_new();

    gtk_builder_add_from_file(builder, "main.glade", NULL);
    
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));
    GtkWidget *calc_textbox = GTK_WIDGET(gtk_builder_get_object(builder, "calc_textbox"));
    GtkWidget *button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    GtkWidget *button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
    GtkWidget *button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    GtkWidget *button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
    GtkWidget *button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    GtkWidget *button6 = GTK_WIDGET(gtk_builder_get_object(builder, "button6"));
    GtkWidget *button7 = GTK_WIDGET(gtk_builder_get_object(builder, "button7"));
    GtkWidget *button8 = GTK_WIDGET(gtk_builder_get_object(builder, "button8"));
    GtkWidget *button9 = GTK_WIDGET(gtk_builder_get_object(builder, "button9"));
    GtkWidget *button0 = GTK_WIDGET(gtk_builder_get_object(builder, "button0"));

    GtkWidget *minus = GTK_WIDGET(gtk_builder_get_object(builder, "minus"));
    GtkWidget *plus = GTK_WIDGET(gtk_builder_get_object(builder, "plus"));
    GtkWidget *kakeru = GTK_WIDGET(gtk_builder_get_object(builder, "kakeru"));
    GtkWidget *waru = GTK_WIDGET(gtk_builder_get_object(builder, "waru"));
    GtkWidget *kotae = GTK_WIDGET(gtk_builder_get_object(builder, "kotae"));
    GtkWidget *dot = GTK_WIDGET(gtk_builder_get_object(builder, "dot"));
    GtkWidget *delete = GTK_WIDGET(gtk_builder_get_object(builder, "delete"));
    
    gtk_widget_set_name(window, "window_0");
    gtk_widget_set_name(calc_textbox, "calc_textbox");
    gtk_widget_set_name(button1, "button1");
    gtk_widget_set_name(button2, "button2");
    gtk_widget_set_name(button3, "button3");
    gtk_widget_set_name(button4, "button4");
    gtk_widget_set_name(button5, "button5");
    gtk_widget_set_name(button6, "button6");
    gtk_widget_set_name(button7, "button7");
    gtk_widget_set_name(button8, "button8");
    gtk_widget_set_name(button9, "button9");
    gtk_widget_set_name(button0, "button0");

    gtk_widget_set_name(minus, "minus");
    gtk_widget_set_name(plus, "plus");
    gtk_widget_set_name(kakeru, "kakeru");
    gtk_widget_set_name(waru, "waru");
    gtk_widget_set_name(kotae, "kotae");
    gtk_widget_set_name(dot, "dot");
    gtk_widget_set_name(delete, "delete");

    gtk_style_context_add_class(gtk_widget_get_style_context(button1), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(button2), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(button3), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(button4), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(button5), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(button6), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(button7), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(button8), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(button9), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(button0), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(minus), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(plus), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(kakeru), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(waru), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(kotae), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(dot), "button_style1");
    gtk_style_context_add_class(gtk_widget_get_style_context(delete), "button_style1");

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);

    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 550);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
    g_signal_connect(button1, "clicked", G_CALLBACK(plus_1), calc_textbox);
    g_signal_connect(button2, "clicked", G_CALLBACK(plus_2), calc_textbox);
    g_signal_connect(button3, "clicked", G_CALLBACK(plus_3), calc_textbox);
    g_signal_connect(button4, "clicked", G_CALLBACK(plus_4), calc_textbox);
    g_signal_connect(button5, "clicked", G_CALLBACK(plus_5), calc_textbox);
    g_signal_connect(calc_textbox, "changed", G_CALLBACK(on_entry_changed), NULL);
    g_signal_connect(button6, "clicked", G_CALLBACK(plus_6), calc_textbox);
    g_signal_connect(button7, "clicked", G_CALLBACK(plus_7), calc_textbox);
    g_signal_connect(button8, "clicked", G_CALLBACK(plus_8), calc_textbox);
    g_signal_connect(button9, "clicked", G_CALLBACK(plus_9), calc_textbox);
    g_signal_connect(button0, "clicked", G_CALLBACK(plus_0), calc_textbox);
    g_signal_connect(plus, "clicked", G_CALLBACK(plus_plus), calc_textbox);
    g_signal_connect(minus, "clicked", G_CALLBACK(minus_plus), calc_textbox);
    g_signal_connect(kakeru, "clicked", G_CALLBACK(kakeru_plus), calc_textbox);
    g_signal_connect(waru, "clicked", G_CALLBACK(waru_plus), calc_textbox);
    g_signal_connect(kotae, "clicked", G_CALLBACK(kotae_plus), calc_textbox);
    g_signal_connect(dot, "clicked", G_CALLBACK(dot_plus), calc_textbox);
    g_signal_connect(delete, "clicked", G_CALLBACK(delete_box), calc_textbox);
    

    gtk_widget_show_all(window);
    

    gtk_main();
    
    return 0;
}

