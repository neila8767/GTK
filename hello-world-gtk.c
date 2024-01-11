#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h> 
#include <glib.h>
#include <cairo.h>  //version2
#include <stdlib.h> // Pour la fonction rand
#include <time.h>   // Pour initialiser la graine de rand
//ajouter des messages tels que fin ajout, fin tri, fin ....operation
//revoir insertion, suppression-->conversion d'un float
//revoir les affichages et asssurer la cohérence entre les widget
//faire la coloration des frames
//faire la barre
//faire la progression
//faire le bouton de vitesse
//faire les controles de type des vals à ajouter, rechercher ou supprimer
//verifier taille max du tableau 100
//lancer les versions du git
//legende pour le tri+++ regler l erreur de tri
GtkWidget *window;
GtkWidget *box;
GtkWidget *grid;
GtkWidget *Dgrid;
GtkWidget *paned; 
GtkWidget *button;
GtkWidget *Abutton;
GtkWidget *Dbutton;
GtkWidget *Gobutton;
GtkWidget *entry;
GtkWidget *entry1;
GtkWidget *label;
GtkWidget *label1;
GtkWidget *info;
int dim=-1;
float tab[100];
static int iteration = 0;
static int iiteration = 0;
static int jiteration = 0;
static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    double bar_height = (double)GPOINTER_TO_INT(user_data);
    double x, y;
   // gtk_widget_compute_point(Dgrid, 0, 0, &x, &y);
    // Dessiner le rectangle avec la hauteur spécifiée
    cairo_rectangle(cr, 10, 10, 50,50); //(double)gtk_widget_get_width(widget), (double)gtk_widget_get_height(widget));
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0); // Couleur du rectangle (bleu)
    cairo_fill(cr);
    return FALSE;
}

gboolean delayed_function (gpointer user_data) {
        char str[10];
        gchar *text = g_strdup_printf("%.2f", tab[iteration]);
        GtkWidget *frame = gtk_frame_new(text);
        sprintf(str, "%d", iteration);
        GtkWidget *ind = gtk_label_new(str);   //gtk_frame_new(str);//gtk_label_new(str);
  /*      GtkWidget *drawing_area = gtk_drawing_area_new();
        gtk_widget_set_visible(drawing_area, TRUE);
        
        g_signal_connect(GTK_WIDGET(drawing_area), "draw", G_CALLBACK(on_draw_event), GINT_TO_POINTER(round(tab[iteration])));*/
         //   
        //gtk_widget_queue_draw(GTK_WIDGET(drawing_area));
        //gtk_widget_queue_resize(GTK_WIDGET(drawing_area));//    _draw(GTK_WIDGET(drawing_area));
        //gtk_widget_s
        //gtk_widget_show(GTK_WIDGET(drawing_area));
        //gtk_window_present(GTK_WIDGET(drawing_area));
/*        gtk_grid_attach(GTK_GRID(Dgrid), drawing_area, iteration + 5, 10, 1, 1);
        gtk_widget_queue_draw(GTK_WIDGET(drawing_area));
        //g_signal_emit_by_name(GTK_WIDGET(widget), "draw", NULL);
        //gtk_widget_set_size_request(GTK_WIDGET(frame), -1, round(tab[i]));
        //GdkRGBA color;
        //gdk_rgba_parse(&color, "red");
        // Définir la couleur de fond du cadre
        //gtk_widget_override_background_color(GTK_WIDGET(frame), GTK_STATE_FLAG_NORMAL, &color);
        // Créer un fournisseur de style CSS
        GtkCssProvider *provider = gtk_css_provider_new();
        gtk_css_provider_load_from_string(provider, "GtkFrame { background-color: red; }"); //, -1, NULL);

        // Appliquer le fournisseur de style CSS au contexte de style du cadre
        //GtkStyleContext *context = gtk_widget_get_style_context(frame);
        GdkDisplay *display = gtk_widget_get_display(frame);
        gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);*/


        gtk_grid_attach(GTK_GRID(Dgrid), frame, iteration + 5, 29, 1, 1);
                                         //gtk_widget_set_size_request(GTK_WIDGET(ind), -1, -1);
        gtk_grid_attach(GTK_GRID(Dgrid), ind, iteration + 5, 30, 1, 1);
        g_free(text);
        iteration++;  
        if (iteration < dim) {
            g_timeout_add_seconds(0.1, delayed_function, NULL);
        } else {
            iteration=0;
        }

    return G_SOURCE_REMOVE;
}

/*void displayTab(GtkWidget *widget, int dim, float tab[dim]) {
    gtk_widget_set_visible(GTK_GRID(Dgrid),false);
    Dgrid = gtk_grid_new();
    //gtk_widget_set_visible(GTK_GRID(Dgrid),true);
    gtk_widget_set_hexpand(Dgrid, TRUE);
    gtk_widget_set_vexpand(Dgrid, TRUE);
    gtk_box_append(GTK_BOX(box), Dgrid); 
    gtk_widget_set_visible(GTK_GRID(Dgrid),true);    
    //gtk_grid_set_row_homogeneous(GTK_GRID(Dgrid), FALSE);
    g_timeout_add(0.1, delayed_function, NULL);
}*/
void displayTab(GtkWidget *widget, int dim, float tab[dim]) {
    char str[10],texte[40];
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),false);
    Dgrid = gtk_grid_new();
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),true);
    gtk_widget_set_hexpand(Dgrid, TRUE);
    gtk_widget_set_vexpand(Dgrid, TRUE);
    gtk_box_append(GTK_BOX(box), Dgrid); 
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),true); 
    sprintf(texte,"Affichage du tableau de dimension %d\n",dim);   
    label = gtk_label_new(texte);
    gtk_grid_attach(GTK_GRID(Dgrid), label, 1, 5, 2, 1);
    for (int i=0;i<dim;i++){
        gchar *text = g_strdup_printf("%.2f", tab[i]);
        GtkWidget *frame = gtk_frame_new(text);
        sprintf(str, "%d", i);
        GtkWidget *ind = gtk_label_new(str);
        gtk_grid_attach(GTK_GRID(Dgrid), ind, i + 5, 20, 1, 1);
        gtk_grid_attach(GTK_GRID(Dgrid), frame, i + 5, 21, 1, 1);
        g_free(text);
    }
}

void displayTabAnim(GtkWidget *widget, int dim, float tab[dim],int p,int j) {
    char str[10];
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),false);
    Dgrid = gtk_grid_new();
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),true);
    gtk_widget_set_hexpand(Dgrid, TRUE);
    gtk_widget_set_vexpand(Dgrid, TRUE);
    gtk_box_append(GTK_BOX(box), Dgrid); 
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),true);    
    for (int i=0;i<dim;i++){
        gchar *text = g_strdup_printf("%.2f", tab[i]);
        GtkWidget *frame = gtk_frame_new(text);
        if(p==1 && (i==j || i==j+1)){
            label = gtk_label_new("X");
        }
        if(p==0 && (i==j || i==j+1)){
            label = gtk_label_new("O");
        }
        if(i!=j && i!=j+1){
            label = gtk_label_new(" ");
        }
        sprintf(str, "%d", i);
        GtkWidget *ind = gtk_label_new(str);
        gtk_grid_attach(GTK_GRID(Dgrid), ind, i + 5, 20, 1, 1);
        gtk_grid_attach(GTK_GRID(Dgrid), frame, i + 5, 21, 1, 1);
        gtk_grid_attach(GTK_GRID(Dgrid), label, i+5, 22, 1, 1);
        g_free(text);
    }
}

static void valider (GtkButton *button, gpointer data) {
    entry = GTK_WIDGET(data);
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    dim = atoi(text);
    gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(Gobutton), FALSE);
    srand(time(NULL));
     for (int i = 0; i < dim; ++i) {
        tab[i] = rand() % 100;   // Valeurs aléatoires entre 0 et 99
     }
    displayTab(GTK_WIDGET(Dgrid),dim, tab);
}

static void svalider (GtkButton *button, gpointer data) {
    entry = GTK_WIDGET(data);
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    char *token;
    double nombre;
    char *copyt = g_strdup(text);
    dim=-1;
    token = strtok(copyt, ",");
    while (token != NULL) {
        nombre = strtod(token, NULL);
        dim++;
        tab[dim] = nombre;
        token = strtok(NULL, ",");
    }
    dim++;
    gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(info), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(Gobutton), FALSE);
    displayTab(GTK_WIDGET(Dgrid),dim, tab);
}

void saisie (){
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    label = gtk_label_new("Saisir les données du tableau :");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 5, 2, 1);
    info = gtk_label_new("(utiliser la \",\" comme séparateur et le \".\" pour les décimaux)");
    gtk_grid_attach(GTK_GRID(grid), info, 3, 6, 12, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 3, 5, 4, 1);
    Gobutton = gtk_button_new_with_label("Go");
    g_signal_connect(Gobutton, "clicked", G_CALLBACK(svalider), entry);
    gtk_grid_attach(GTK_GRID(grid), Gobutton, 8, 5, 1, 1);
}

void Dimension (){
    gtk_grid_set_row_spacing(GTK_GRID(grid), 70);
    // Créer une étiquette pour expliquer à l'utilisateur
    label = gtk_label_new("Donner la dimension du tableau :");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 5, 2, 1);
    // Créer une entrée pour la saisie de la valeur
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 3, 5, 1, 1);
    g_signal_connect(entry, "activate", G_CALLBACK(valider), entry);
    // Créer un bouton "Valider"
    Gobutton = gtk_button_new_with_label("Go");

    // Connecter le signal "clicked" à la fonction on_button_clicked
    g_signal_connect(Gobutton, "clicked", G_CALLBACK(valider), entry);
    
    // Ajouter le bouton au grid
    gtk_grid_attach(GTK_GRID(grid), Gobutton, 4, 5, 1, 1);
}


void permute(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}
////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
gboolean delayed_animation (gpointer user_data);
gboolean delayed_i (gpointer user_data);
static void trier (GtkButton *button, gpointer data);
gboolean delayed_permute (gpointer user_data) {
        /*float temp = tab[jiteration];
        tab[jiteration] = tab[jiteration+1];
        tab[jiteration+1] = temp;*/
        permute(&tab[jiteration],&tab[jiteration+1]);
        displayTabAnim(GTK_WIDGET(Dgrid),dim, tab,1,jiteration);
        jiteration++;  
        if (jiteration < dim-iiteration-1) {
            g_timeout_add(4000, delayed_animation, NULL);
        } else {
            iiteration++;
            jiteration = 0;
            g_timeout_add(4000, delayed_i, NULL);
        }

    return G_SOURCE_REMOVE;
}

/////////////////////////////////////////////////
gboolean delayed_animation (gpointer user_data) {
        g_print("passe %d  element j  %d \n", iiteration,jiteration);
        if (tab[jiteration] > tab[jiteration+1]) {
            /*gchar *text1 = g_strdup_printf("%.2f", tab[jiteration]);
            GtkWidget *frame1 = gtk_frame_new(text1);
            gchar *text2 = g_strdup_printf("%.2f", tab[jiteration+1]);
            GtkWidget *frame2 = gtk_frame_new(text2);
            gtk_grid_attach(GTK_GRID(Dgrid), frame1, jiteration + 5, 22, 1, 1);
            gtk_grid_attach(GTK_GRID(Dgrid), frame2, jiteration + 5, 22, 1, 1);  */
            displayTabAnim(GTK_WIDGET(Dgrid),dim, tab,1,jiteration);
            g_timeout_add(4000, delayed_permute,NULL);  
            /*g_free(text1);
            g_free(text2);*/      
        } else {
            displayTabAnim(GTK_WIDGET(Dgrid),dim, tab,0,jiteration);
            jiteration++;
            g_timeout_add(4000, delayed_animation,NULL); 
        }
    return G_SOURCE_REMOVE;
}
/////////
gboolean delayed_i (gpointer user_data) {
        g_print("passe %d  element j  %d \n", iiteration,jiteration);
        if (iiteration < dim-1) {
            g_timeout_add(4000, delayed_animation, NULL);
        } else {
            //displayTab(GTK_WIDGET(Dgrid),dim, tab);
            iiteration=0;
        }
    return G_SOURCE_REMOVE;
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////
static void trier (GtkButton *button, gpointer data) {
  //g_print("passe %d  element j  %d \n", iiteration,iteration);
  g_timeout_add(1, delayed_i,NULL);
}

/*static void trier (GtkButton *button, gpointer data) {
  for (int i = 0; i < dim-1; i++) {
        for (int j = 0; j < dim-i-1; j++) {
            if (tab[j] > tab[j+1]) {
                permute(&tab[j], &tab[j+1]);
                displayTab(GTK_WIDGET(Dgrid),dim, tab,j);
            }
        }
  }
  //displayTab(GTK_WIDGET(Dgrid),dim, tab);
}*/

  
static void rechvalider (GtkButton *button, gpointer data) {
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    float val;
    val = atoi(text);
    g_print("la valeur à supprimer %d\n", val);
    gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(label1), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry1), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(Gobutton), FALSE);
    ///////////////////////////////////////////////////////////////////////////////
    int i=0;
    while ((i<dim) && (tab[i]!=val)){
      i++;
    }
    if(i=dim){
       label = gtk_label_new("La valeur recherchée est inexistente dans le tableau");
       gtk_grid_attach(GTK_GRID(Dgrid), label, 1, 7, 1, 1);
    } else {
       label = gtk_label_new("La valeur recherchée est bien dans le tableau");
       gtk_grid_attach(GTK_GRID(Dgrid), label, 1, 7, 1, 1);
    }
}

static void recherche (GtkButton *button, gpointer data) {
    gtk_grid_set_row_spacing(GTK_GRID(grid), 70);
    // Créer une étiquette pour expliquer à l'utilisateur
    label = gtk_label_new("Donner la valeur :");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 5, 1, 1);
    // Créer une entrée pour la saisie de la valeur
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 2, 5, 1, 1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 0);
    
    Gobutton = gtk_button_new_with_label("Go");

    // Connecter le signal "clicked" à la fonction on_button_clicked
    g_signal_connect(Gobutton, "clicked", G_CALLBACK(rechvalider),NULL);  

    // Ajouter le bouton au grid
    gtk_grid_attach(GTK_GRID(grid), Gobutton, 1, 7, 1, 1);
}

static void suppvalider (GtkButton *button, gpointer data) {
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    float val;
    val = 12.3;    // atoi(text);
    g_print("la valeur à supprimer %d\n", val);
    gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(label1), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry1), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(Gobutton), FALSE);
    ///////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < dim; i++) {
      if (tab[i] == val) {
        // Décalage des éléments pour remplir le trou
        for (int j = i; j < dim - 1; j++) {
            tab[j] = tab[j + 1];
        }
        // décrémenter la dimension 
        dim--;
      }
    displayTab(GTK_WIDGET(Dgrid),dim, tab);
    }
}

static void suppression (GtkButton *button, gpointer data) {
    gtk_grid_set_row_spacing(GTK_GRID(grid), 70);
    // Créer une étiquette pour expliquer à l'utilisateur
    label = gtk_label_new("Donner la valeur :");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 5, 1, 1);
    // Créer une entrée pour la saisie de la valeur
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 2, 5, 1, 1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 0);
    
    Gobutton = gtk_button_new_with_label("Go");

    // Connecter le signal "clicked" à la fonction on_button_clicked
    g_signal_connect(Gobutton, "clicked", G_CALLBACK(suppvalider),NULL);  

    // Ajouter le bouton au grid
    gtk_grid_attach(GTK_GRID(grid), Gobutton, 1, 7, 1, 1);
}

static void insvalider (GtkButton *button, gpointer data) {
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    const gchar *text1 = gtk_editable_get_text(GTK_EDITABLE(entry1));
    int pos,val;
    pos = atoi(text);
    val = atoi(text1);
    g_print("La position  %d   la valeur %d\n", pos,val);
    gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(label1), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry1), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(Gobutton), FALSE);
    ///////////////////////////////////////////////////////////////////////////////
    if (pos < 0 || pos > dim || dim >= 100) {  // 100 max du tableau
        printf("Position invalide ou tableau plein.\n");
    
    } else {
       for (int i = dim; i > pos; i--) {
        tab[i] = tab[i - 1];
    }
    tab[pos] = val;
    dim++;
  }
  displayTab(GTK_WIDGET(Dgrid),dim, tab);
}
static void insertion (GtkButton *button, gpointer data) {
    gtk_grid_set_row_spacing(GTK_GRID(grid), 70);
    // Créer une étiquette pour expliquer à l'utilisateur
    label = gtk_label_new("Donner la position :");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 5, 1, 1);
    // Créer une entrée pour la saisie de la valeur
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 2, 5, 1, 1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 0);
    label1 = gtk_label_new("Donner la valeur :");
    gtk_grid_attach(GTK_GRID(grid), label1, 1, 6, 1, 1);
    // Créer une entrée pour la saisie de la valeur
    entry1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry1, 2, 6, 1, 1);
    // Créer un bouton "Valider"
    Gobutton = gtk_button_new_with_label("Go");

    // Connecter le signal "clicked" à la fonction on_button_clicked
    g_signal_connect(Gobutton, "clicked", G_CALLBACK(insvalider),NULL);

    // Ajouter le bouton au grid
    gtk_grid_attach(GTK_GRID(grid), Gobutton, 1, 7, 1, 1);
}
static void creation (GtkButton *button, gpointer data) {
  gtk_grid_set_row_spacing(GTK_GRID(grid), 0);
  gtk_widget_set_visible(GTK_WIDGET(Dbutton), TRUE);
  gtk_widget_set_visible(GTK_WIDGET(Abutton), TRUE);
}

static void
createRand (GtkWidget *widget, gpointer data){
     gtk_widget_set_visible(GTK_WIDGET(Dbutton), FALSE);
     gtk_widget_set_visible(GTK_WIDGET(Abutton), FALSE);
     Dimension ();
}

static void
createUser (GtkWidget *widget,
             gpointer   data)
{
gtk_widget_set_visible(GTK_WIDGET(Dbutton), FALSE);
gtk_widget_set_visible(GTK_WIDGET(Abutton), FALSE);
saisie();
}

static void
activate (GtkApplication *app,
          gpointer user_data)
{
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Projet C : Opérations sur les tableaux");
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_window_set_child(GTK_WINDOW(window), box);
  grid = gtk_grid_new();
  gtk_widget_set_hexpand(grid, TRUE);
  gtk_widget_set_vexpand(grid, TRUE);
  button = gtk_button_new_with_label ("Création");
  g_signal_connect (button, "clicked", G_CALLBACK (creation), NULL);
  gtk_grid_attach(GTK_GRID (grid), button, 0, 0, 1, 1);
  button = gtk_button_new_with_label ("insertion");        
  g_signal_connect (button, "clicked", G_CALLBACK (insertion), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);
  button = gtk_button_new_with_label ("Suppression");
  g_signal_connect (button, "clicked", G_CALLBACK (suppression), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);
  button = gtk_button_new_with_label ("Recherche élément");
  g_signal_connect (button, "clicked", G_CALLBACK (recherche), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 1, 1);
  button = gtk_button_new_with_label ("Tri à bulles");
  g_signal_connect (button, "clicked", G_CALLBACK (trier), NULL);
  gtk_grid_attach (GTK_GRID (grid), button, 4, 0, 1, 1);
  button = gtk_button_new_with_label ("Quitter");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 0, 1, 1);
  Dbutton = gtk_button_new_with_label ("Données utilisateur");
  g_signal_connect (Dbutton, "clicked", G_CALLBACK (createUser), NULL);
  gtk_grid_attach (GTK_GRID (grid), Dbutton, 0, 1, 2, 1);
  gtk_widget_set_visible(GTK_WIDGET(Dbutton), FALSE);
  Abutton = gtk_button_new_with_label ("Données aléatoires");        
  g_signal_connect (Abutton, "clicked", G_CALLBACK (createRand), NULL);
  gtk_grid_attach (GTK_GRID (grid), Abutton, 0, 2, 2, 1);
  gtk_widget_set_visible(GTK_WIDGET(Abutton), FALSE);
  Dgrid = gtk_grid_new ();
  gtk_widget_set_hexpand(Dgrid, TRUE);
  gtk_widget_set_vexpand(Dgrid, TRUE);
  gtk_box_append(GTK_BOX(box), grid);
  gtk_box_append(GTK_BOX(box), Dgrid);
  gtk_window_present (GTK_WINDOW (window));
}

/*static gboolean draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    // Dessiner un rectangle rouge (par exemple)
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0); // Couleur rouge
    cairo_rectangle(cr, 50, 50, 200, 100); // Coordonnées et dimensions du rectangle
    cairo_fill(cr); // Remplir le rectangle avec la couleur spécifiée

    return FALSE; // Indiquer que le dessin est terminé
}
static void
activate (GtkApplication *app,
          gpointer user_data)
{
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Projet C : Opérations sur les tableaux");
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
  GtkWidget *drawing_area = gtk_drawing_area_new();
  
  gtk_window_set_child(GTK_WINDOW(window), drawing_area);
  g_signal_connect(GTK_WIDGET(drawing_area), "expose-event", G_CALLBACK(draw_callback), NULL);

  gtk_window_present (GTK_WINDOW (window));
}*/

int
main (int argc,char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("project.Algo", G_APPLICATION_DEFAULT_FLAGS);
  //app = gtk_application_new ("project.Algo".G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
  status = g_application_run(G_APPLICATION(app),argc,argv);
  g_object_unref(app);
  return status;
}