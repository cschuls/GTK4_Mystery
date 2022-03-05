#include <gtk/gtk.h>

GtkWidget	    *window;
GtkWidget	    *fixed;
GtkWidget	    *button;
GtkWidget       *progressbar1;
GtkWidget       *progressbar2;
GtkWidget	    *timer;
GtkBuilder      *builder;

GtkCssProvider  *cssprovider1;
GtkCssProvider  *cssprovider2;

gboolean        run_progress;

guint           beginning_value;
guint           ending_value;

gboolean timer_handler(GtkWidget *);
void on_window_destroy();

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    builder      = gtk_builder_new_from_resource("/ProgressBar/ProgressBar.glade");
    window       = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    fixed        = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    button       = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    progressbar1 = GTK_WIDGET(gtk_builder_get_object(builder, "progressbar1"));
    progressbar2 = GTK_WIDGET(gtk_builder_get_object(builder, "progressbar2"));
    cssprovider1 = gtk_css_provider_new();
    cssprovider2 = gtk_css_provider_new();

    beginning_value = 0;
    ending_value    = 100;

    gtk_css_provider_load_from_data(cssprovider1, "progressbar trough { background-image: none; background-color: #ffffff; min-height: 10px; border-radius: 0px; box-shadow: none;} \
     progressbar progress { background-image: none; background-color: #b3a472; min-height: 10px; border-radius: 0px; box-shadow: none;}", -1, NULL);
    gtk_css_provider_load_from_data(cssprovider2, "progressbar trough { background-image: none; background-color: #ffffff; min-height: 10px; border-radius: 0px; box-shadow: none;} \
     progressbar progress { background-image: none; background-color: #92b372; min-height: 10px; border-radius: 0px; box-shadow: none;}", -1, NULL);

    gtk_style_context_add_provider(gtk_widget_get_style_context(progressbar1), GTK_STYLE_PROVIDER(cssprovider1), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_style_context_add_provider(gtk_widget_get_style_context(progressbar2), GTK_STYLE_PROVIDER(cssprovider2), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    gtk_builder_connect_signals(builder, NULL);

    gtk_window_set_title (GTK_WINDOW(window), "Progress Bar Demonstration");

    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progressbar1), (gdouble) 0.00);
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(progressbar2), (gdouble) 0.00);

    run_progress = FALSE;

    g_timeout_add(70, (GSourceFunc) timer_handler, timer);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;

}

void on_window_destroy()
{
    gtk_main_quit();
}

void on_button_clicked(GtkButton *b)
{
    printf("Start button clicked\n");
    beginning_value = 0;
    run_progress    = TRUE;
}

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
