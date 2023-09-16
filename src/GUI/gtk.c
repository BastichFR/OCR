/*

#include <gtk.h>

void load_image(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;

    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File",
                                         GTK_WINDOW(main_window),
                                         action,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "Open",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Images");
    gtk_file_filter_add_pattern(filter, "*.png");
    gtk_file_filter_add_pattern(filter, "*.jpg");
    gtk_file_filter_add_pattern(filter, "*.jpeg");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);

        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image_area), pixbuf);
        g_object_unref(pixbuf);

        gtk_widget_set_sensitive(launch_button, TRUE);
	gtk_label_set_text(GTK_LABEL(status_label), "");

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

int gtk_main() {
    gtk_init(NULL, NULL);

    GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "EPITA - Sudoku OCR");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 960, 630);
    gtk_widget_set_size_request(main_window, 960, 630);    
    gtk_container_set_border_width(GTK_CONTAINER(main_window), 10);
    gtk_window_set_resizable(GTK_WINDOW(main_window), FALSE);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request(scrolled_window, 500, 400);
    GtkWidget *image_area = gtk_image_new();
    gtk_container_add(GTK_CONTAINER(scrolled_window), image_area);
    gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 0);

    GtkWidget *load_button = gtk_button_new_with_label("Load image");
    g_signal_connect(load_button, "clicked", G_CALLBACK(load_image), NULL);
    gtk_box_pack_start(GTK_BOX(box), load_button, FALSE, FALSE, 0);

    GtkWidget *launch_button = gtk_button_new_with_label("Launch");
    gtk_widget_set_sensitive(launch_button, FALSE);
    gtk_box_pack_start(GTK_BOX(box), launch_button, FALSE, FALSE, 0);

    GtkWidget *status_label = gtk_label_new("No file loaded");
    gtk_box_pack_start(GTK_BOX(box), status_label, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(main_window), box);

    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(main_window);

    gtk_main();

    return 0;
}
*/
