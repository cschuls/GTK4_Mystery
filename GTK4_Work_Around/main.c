#include <gtk/gtk.h>

GtkProgressBar  *progressbar1;
GtkProgressBar  *progressbar2;
GtkWidget       *timer;

gboolean        run_progress;
guint           beginning_value;
guint           ending_value;

gboolean timer_handler(GtkWidget *timer)
{
    if (run_progress)
    {
        beginning_value++;
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progressbar1), (gdouble) beginning_value/ending_value );
        gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progressbar2), (gdouble) beginning_value/ending_value );

        if (beginning_value >= ending_value)
            run_progress = FALSE;
    }

    return TRUE; // FALSE kills the timer
}

static void do_progress (GtkWidget *widget, gpointer data)
{
    beginning_value = 0;
    run_progress    = TRUE;
}

static void activate (GtkApplication* app, gpointer user_data)
{
    GtkBuilder      *builder;
    GtkCssProvider  *provider;
    GtkStyleContext *context;
    GtkWindow       *window;
    GtkButton       *button1;
    GdkDisplay      *display;

    beginning_value = 0;
    ending_value    = 100;

    /* Construct a GtkBuilder instance and load our UI description */

    builder      = gtk_builder_new ();

    gtk_builder_add_from_resource (builder, "/Prog/progressbar.ui", NULL);

    window       = GTK_WINDOW(gtk_builder_get_object (builder, "window"));
    button1      = GTK_BUTTON(gtk_builder_get_object (builder, "button1"));
    progressbar1 = GTK_PROGRESS_BAR(gtk_builder_get_object (builder, "progressbar1"));
    progressbar2 = GTK_PROGRESS_BAR(gtk_builder_get_object (builder, "progressbar2"));
    provider     = gtk_css_provider_new();
    display      = gtk_widget_get_display (GTK_WIDGET (window));

    gtk_window_set_application (window, app);
    gtk_window_set_default_size (window, 400, 200);

    /* Connect signal handlers to the constructed widgets. */

    g_signal_connect (button1, "clicked", G_CALLBACK (do_progress), NULL);

    /* Set up CSS customizations at the display level */

    gtk_css_provider_load_from_data(provider, "#prog1 trough { background-image: none; background-color: #ffffff; min-height: 10px; border-radius: 0px; box-shadow: none;} \
        #prog1 trough progress { background-image: none; background-color: #b3a472; min-height: 10px; border-radius: 0px; box-shadow: none;} \
        #prog2 trough { background-image: none; background-color: #ffffff; min-height: 10px; border-radius: 0px; box-shadow: none;} \
        #prog2 trough progress { background-image: none; background-color: #92b372; min-height: 10px; border-radius: 0px; box-shadow: none;} ", -1);

    gtk_style_context_add_provider_for_display (display, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progressbar1), (gdouble) 0.00);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progressbar2), (gdouble) 0.00);

    g_timeout_add(40, (GSourceFunc) timer_handler, timer);

    gtk_widget_show (GTK_WIDGET(window));
}

int main (int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("local.craig.progressbar", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
