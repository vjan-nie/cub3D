# cub3d

## Estructura general del proyecto

```bash
cub3D/
├── src/
│   ├── core/           # Núcleo del programa
│   │   ├── cub3d.c           (main, inicialización)
│   │   ├── key_handler.c     (gestión de teclas)
│   │   └── utils.c           (utilidades generales)
│   │
│   ├── parser/         # Parsing del archivo .cub
│   │   ├── map.c
│   │   ├── map_utils.c
│   │   ├── map_utils2.c
│   │   ├── normalize_map.c
│   │   ├── parse_map.c
│   │   ├── parse_map_utils.c
│   │   └── validate_map.c
│   │
│   └── render/         # Renderizado y ray-casting
│       ├── movement.c
│       ├── move_rotate.c
│       ├── move_wasd.c
│       ├── player.c
│       ├── player_utils.c
│       ├── raycasting.c
│       ├── raycasting_utils.c
│       ├── render.c
│       └── textures.c
│
├── includes/           # Headers
├── libft/             # Tu librería libft
├── minilibx/          # MiniLibX para Linux
└── obj/               # Objetos compilados
```
## Flujo

```bash
main()
  ↓
  ├─ Validar argumentos (argc == 2)
  ↓
  ├─ init_cub3d()
  │    ↓
  │    ├─ ft_bzero()
  │    ├─ init_graphics() → mlx_init()
  │    └─ load_game()
  │         ↓
  │         ├─ load_and_validate_map() → Parser completo
  │         ├─ init_window() → Crear ventana + frame buffer
  │         ├─ load_textures() → Cargar 4 texturas XPM
  │         └─ init_player() → Posición y vectores dir/plane
  ↓
  ├─ mlx_hook() → Configurar eventos
  │    ├─ KeyPress (2)
  │    ├─ KeyRelease (3)
  │    └─ DestroyNotify (17) → Cerrar ventana
  ↓
  ├─ mlx_loop_hook() → Asignar main_loop()
  ↓
  └─ mlx_loop() → Iniciar el engine
       ↓
       └─ [Cada frame ejecuta main_loop()]
            ↓
            ├─ Comprobar ESC
            ├─ update_player() → Procesar input
            ├─ render_frame() → Ray-casting + dibujado
            └─ mlx_put_image_to_window() → Mostrar
```