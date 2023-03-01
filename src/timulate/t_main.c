void (*main_loop_func)(void);

void timulate_main_loop_func_set(void *func)
{
    main_loop_func = func;
}

void timulate_main_loop_launch(void)
{
    while (1)
        main_loop_func();
}
