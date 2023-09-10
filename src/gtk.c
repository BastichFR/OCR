#include <gtk-3.0/gtk/gtk.h>

int window() {
    GtkWidget *window;

    // Initialiser GTK
    gtk_init(NULL, NULL);

    // Créer une nouvelle fenêtre
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Définir le titre de la fenêtre
    gtk_window_set_title(GTK_WINDOW(window), "Ma première fenêtre GTK");

    // Définir la taille de la fenêtre
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Connecter une fonction pour gérer la fermeture de la fenêtre
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Afficher tous les widgets
    gtk_widget_show_all(window);

    // Démarrer la boucle principale GTK
    gtk_main();

    return 0;
}
