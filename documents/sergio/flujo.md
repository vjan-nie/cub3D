## Flujo principal

```c
main()
├─> init_cub3d()
│ ├─> init_graphics() // MLX init
│ └─> load_game()
│ ├─> load_and_validate_map()
│ ├─> init_window()
│ ├─> load_textures()
│ └─> init_player()
└─> mlx_loop()
```

## Flujo de parseo

```c
load_and_validate_map()
  ├─> read_file_lines()           // Lee archivo completo
  │     ├─> check_extension()     // Valida .cub
  │     ├─> accumulate_gnl()      // Lee con GNL
  │     └─> ft_split('\n')        // Divide en líneas
  │
  ├─> parse_config()              // Extrae texturas y colores
  ├─> parse_map()                 // Extrae grid del mapa
  ├─> normalize_map()             // Rectangulariza
  └─> validate_map()              // Valida cierre y jugador
```

## Validacion configuración

```c
parse_config()
  ├─> parse_config_aux()
  │     ├─> parse_texture()   // NO, SO, WE, EA
  │     └─> parse_color()     // F, C
  │           └─> parse_rgb() // R,G,B validation
  └─> Verifica exactamente 6 entradas
```

## Parseo del mapa

```c
parse_map()
  ├─> skip_config()           // Encuentra inicio del mapa
  ├─> count_map_lines()       // Calcula altura
  ├─> malloc(grid)            // Aloca memoria
  ├─> copy_map_lines()        // Copia líneas
  └─> get_max_line_length()   // Calcula ancho máximo
```
