#include "include/GUI/interface.h"


GtkBuilder *builder;
GtkWidget *main;
GtkWidget *processing;


void start_button(GtkButton *button, gpointer user_data){
    gtk_widget_hide(main);
    gtk_widget_show(processing);
}


int home(){


    gtk_init();

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "src/GUI/interface.glade", &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return 1;
    }

    // windows
    main = GTK_WIDGET(gtk_builder_get_object(builder, "main"));
    processing = GTK_WIDGET(gtk_builder_get_object(builder, "processing"));

    // first page
    GtkWidget *start_button = GTK_WIDGET(gtk_builder_get_object(builder, "start_button"));
    g_signal_connect(bouton_page1, "clicked", G_CALLBACK(start_button), NULL);

    GtkWidget *bouton_page2 = GTK_WIDGET(gtk_builder_get_object(builder, "bouton_page2"));
    g_signal_connect(bouton_page2, "clicked", G_CALLBACK(afficher_page2), NULL);



    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "src/GUI/style.css", NULL);

    GdkScreen *screen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(screen,
                                             GTK_STYLE_PROVIDER(cssProvider),
                                             GTK_STYLE_PROVIDER_PRIORITY_USER);


    return 0;
}