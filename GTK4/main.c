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
    GtkCssProvider  *provider1;
    GtkCssProvider  *provider2;
    GtkCssProvider  *provider3;
    GtkCssProvider  *provider4;
    GtkStyleContext *context;
    GtkWindow       *window;
    GtkLabel        *label1;
    GtkButton       *button1;

    beginning_value = 0;
    ending_value    = 100;

    /* Construct a GtkBuilder instance and load our UI description */

    builder      = gtk_builder_new ();

    gtk_builder_add_from_resource (builder, "/Prog/progressbar.ui", NULL);

    window       = GTK_WINDOW(gtk_builder_get_object (builder, "window"));
    button1      = GTK_BUTTON(gtk_builder_get_object (builder, "button1"));
    progressbar1 = GTK_PROGRESS_BAR(gtk_builder_get_object (builder, "progressbar1"));
    progressbar2 = GTK_PROGRESS_BAR(gtk_builder_get_object (builder, "progressbar2"));
    label1       = GTK_LABEL(gtk_builder_get_object (builder, "label1"));
    provider1    = gtk_css_provider_new();
    provider2    = gtk_css_provider_new();
    provider3    = gtk_css_provider_new();
    provider4    = gtk_css_provider_new();

    gtk_window_set_application (window, app);
    gtk_window_set_default_size (window, 400, 200);

    /* Connect signal handlers to the constructed widgets. */

    g_signal_connect (button1, "clicked", G_CALLBACK (do_progress), NULL);

    printf("CSS Name: %s\n", gtk_widget_get_css_name(GTK_WIDGET(button1)));
    printf("CSS Name: %s\n", gtk_widget_get_css_name(GTK_WIDGET(label1)));
    printf("CSS Name: %s\n", gtk_widget_get_css_name(GTK_WIDGET(progressbar1)));
    printf("CSS Name: %s\n", gtk_widget_get_css_name(GTK_WIDGET(progressbar2)));

    /* Set up CSS customizations */

    gtk_css_provider_load_from_data(provider1, "progressbar trough { background-image: none; background-color: #ffffff; min-height: 10px; border-radius: 0px; box-shadow: none;} \
     progressbar trough progress { background-image: none; background-color: #b3a472; min-height: 10px; border-radius: 0px; box-shadow: none;}", -1);
    context = gtk_widget_get_style_context(GTK_WIDGET(progressbar1));
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    printf("Context: %s\n", gtk_style_context_to_string(context, GTK_STYLE_CONTEXT_PRINT_SHOW_STYLE));

    gtk_css_provider_load_from_data(provider2, "progressbar trough { background-image: none; background-color: #ffffff; min-height: 10px; border-radius: 0px; box-shadow: none;} \
     progressbar trough progress { background-image: none; background-color: #92b372; min-height: 10px; border-radius: 0px; box-shadow: none;}", -1);
    context = gtk_widget_get_style_context(GTK_WIDGET(progressbar2));
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider2), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    printf("Context: %s\n", gtk_style_context_to_string(context, GTK_STYLE_CONTEXT_PRINT_SHOW_STYLE));

    gtk_css_provider_load_from_data(provider3, "button {background-image: none; color: #0000ff;}", -1);
    context = gtk_widget_get_style_context(GTK_WIDGET(button1));
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider3), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    printf("Context: %s\n", gtk_style_context_to_string(context, GTK_STYLE_CONTEXT_PRINT_SHOW_STYLE));

    gtk_css_provider_load_from_data(provider4, "label {background-image: none; background-color: #ccffcc;}", -1);
    context = gtk_widget_get_style_context(GTK_WIDGET(label1));
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider4), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    printf("Context: %s\n", gtk_style_context_to_string(context, GTK_STYLE_CONTEXT_PRINT_SHOW_STYLE));

    /* Temporary code for testing display level CSS override */
    /* Commented out when attempting to run the application with application level CSS overrides */

    //GdkDisplay *display;
    //display = gtk_widget_get_display (GTK_WIDGET (window));
    //gtk_style_context_add_provider_for_display (display, GTK_STYLE_PROVIDER (provider2), GTK_STYLE_PROVIDER_PRIORITY_USER);

    /* End of temporary code */

    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progressbar1), (gdouble) 0.80);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progressbar2), (gdouble) 0.50);

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
