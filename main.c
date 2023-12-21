#include <gtk/gtk.h>

int count = 0;

void count_button(GtkWidget *wid, gpointer ptr) {
  char buffer[30];
  count++;
  sprintf(buffer, "Button pressed %d times", count);
  gtk_label_set_text(GTK_LABEL(ptr), buffer);
}

static void save_file(GtkWidget *btn, gpointer ptr) {
  GtkWidget *sch = gtk_file_chooser_dialog_new(
      "Save file", GTK_WINDOW(ptr), GTK_FILE_CHOOSER_ACTION_SAVE, "Cancel",
      GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);

  if (gtk_dialog_run(GTK_DIALOG(sch)) == GTK_RESPONSE_ACCEPT) {
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(sch));
    g_print("Saving to: %s\n", filename);
    g_free(filename);
  }
}

void end_program(GtkWidget *wid, gpointer ptr) { gtk_main_quit(); }

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);
  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  GtkWidget *btn = gtk_button_new_with_label("Close window");
  g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
  g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);

  GtkWidget *lbl = gtk_label_new("My label");

  GtkWidget *btn2 = gtk_button_new_with_label("Count button");
  g_signal_connect(btn2, "clicked", G_CALLBACK(count_button), lbl);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  GtkWidget *fc_btn = gtk_button_new_with_label("Save file");
  g_signal_connect(fc_btn, "clicked", G_CALLBACK(save_file), win);

  GtkWidget *scale1 =
      gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);

  gtk_box_pack_start(GTK_BOX(box), btn2, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), lbl, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), btn, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), fc_btn, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), scale1, FALSE, FALSE, 50);
  gtk_container_add(GTK_CONTAINER(win), box);

  gtk_widget_show_all(win);
  gtk_main();
  return 0;
}
