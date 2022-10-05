#include "minirt.h"

//parser : Einlesen  des Files mit gnl, ueberpruefen ob richtiges Fomrat, richtige Range

// Aufbau des Fensters, wie in FdF? Geht das schneller?

//Annahme: Eingabe erfolgt mit ./minirt file.rt

// malloc protect...

void leaks()
{
    system("leaks minirt");
}

int main(int argc, char *argv[])
{
    t_scene     scene;
    t_scene     *scene_free = NULL;
    t_graphic   graphic;

    atexit(leaks);
    if (argc != 2)
        text_error("Not the right input - must be of form ./minirt file.rt\n");
    set_scene_null(&scene, &graphic);
    parser(&scene, argv[1]);
    scene = built_graphic(scene, graphic);
    scene_free = &scene;
    free_scene(&scene_free);
    return (0);
}
