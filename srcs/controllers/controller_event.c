/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:55:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/23 16:22:40 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_events.h>
#include <libft_base/io.h>
#include "rt.h"

static t_filter			cycle_filter(t_filter current)
{
	if (current == FILTER_NONE)
		return (FILTER_RED);
	else if (current == FILTER_RED)
		return (FILTER_GREEN);
	else if (current == FILTER_GREEN)
		return (FILTER_BLUE);
	else if (current == FILTER_BLUE)
		return (FILTER_GREY);
	else if (current == FILTER_GREY)
		return (FILTER_BLACK_WHITE);
	else if (current == FILTER_BLACK_WHITE)
		return (FILTER_NEG);
	return (FILTER_NONE);
}

void					on_controller_button_pressed(void *event, t_rt *core)
{
	SDL_ControllerButtonEvent	*e;

	e = (SDL_ControllerButtonEvent *)event;
	if (e->button == SDL_CONTROLLER_BUTTON_GUIDE)
		on_window_closing(core);
	else if (e->button == SDL_CONTROLLER_BUTTON_Y)
		on_key_pressed(SDLK_UP, core);
	else if (e->button == SDL_CONTROLLER_BUTTON_A)
		on_key_pressed(SDLK_DOWN, core);
	else if (e->button == SDL_CONTROLLER_BUTTON_B)
		on_key_pressed(SDLK_RIGHT, core);
	else if (e->button == SDL_CONTROLLER_BUTTON_X)
		on_key_pressed(SDLK_LEFT, core);
	else if (e->button == SDL_CONTROLLER_BUTTON_LEFTSTICK)
	{
		core->scene.filter = cycle_filter(core->scene.filter);
		on_key_pressed(core->scene.filter, core);
		on_key_released(core->scene.filter, core);
	}
}

void					on_controller_button_released(void *event, t_rt *core)
{
	SDL_ControllerButtonEvent	*e;

	e = (SDL_ControllerButtonEvent *)event;
	if (e->button == SDL_CONTROLLER_BUTTON_Y)
		on_key_released(SDLK_UP, core);
	else if (e->button == SDL_CONTROLLER_BUTTON_A)
		on_key_released(SDLK_DOWN, core);
	else if (e->button == SDL_CONTROLLER_BUTTON_B)
		on_key_released(SDLK_RIGHT, core);
	else if (e->button == SDL_CONTROLLER_BUTTON_X)
		on_key_released(SDLK_LEFT, core);
}

void					on_controller_connect(Sint32 id, t_rt *core)
{
	ft_putstr("[connected] controller: ");
	ft_putnbr((int)id);
	ft_putchar('\n');
	controller_update(&core->controller);
}

void					on_controller_disconnect(Sint32 id, t_rt *core)
{
	ft_putstr("[disconnected] controller: ");
	ft_putnbr((int)id);
	ft_putchar('\n');
	SDL_GameControllerClose(core->controller.controller);
	core->controller.controller = NULL;
	controller_update(&core->controller);
}
