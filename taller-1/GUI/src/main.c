#include <gtk/gtk.h>
//#include "flex.h"

int PHENOTYPIC_MODE = 0;
int GENOTYPIC_MODE = 1;
int MODE = 0;
GtkWidget *editorModeButton;
GtkWidget *editorTextView;
GtkWidget *outputTextView;
GtkTextBuffer *editorTextBuffer;
GtkTextBuffer *outputTextBuffer;
GtkTextBuffer *outputTextBuffer;

int main(int argc, char *argv[]) {
	yylex();


	GtkBuilder *builder;
	GtkWidget *window;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "glade/main-window.glade", NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "main-window"));
	gtk_builder_connect_signals(builder, NULL);

	editorModeButton = GTK_WIDGET(
			gtk_builder_get_object(builder, "editorMode"));
	editorTextView = GTK_WIDGET(gtk_builder_get_object(builder, "editor"));
	outputTextView = GTK_WIDGET(gtk_builder_get_object(builder, "output"));
	editorTextBuffer = gtk_text_view_get_buffer(editorTextView);
	outputTextBuffer = gtk_text_view_get_buffer(outputTextView);

	g_object_unref(builder);
	gtk_widget_show(window);
	gtk_main();

	return 0;
}

void mainWindowDestroyed() {
	gtk_main_quit();
}

void buttonActivated() {
	if (MODE == PHENOTYPIC_MODE) {
		MODE = GENOTYPIC_MODE;
		gtk_button_set_label(GTK_BUTTON(editorModeButton), "MODO GENOTIPICO");
	} else {
		MODE = PHENOTYPIC_MODE;
		gtk_button_set_label(GTK_BUTTON(editorModeButton), "MODO FENOTIPICO");
	}
}

void keyPressedInEditor() {
	GtkTextIter start, end;
	char *text;
	int size;

	if (MODE == GENOTYPIC_MODE) {
		size = gtk_text_buffer_get_char_count(editorTextBuffer);
		gtk_text_buffer_get_start_iter(editorTextBuffer, &start);
		gtk_text_buffer_get_end_iter(editorTextBuffer, &end);
		text = gtk_text_buffer_get_text(editorTextBuffer, &start, &end, FALSE);
		gtk_text_buffer_set_text(outputTextBuffer, text, size);
	}
}
