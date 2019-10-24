/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 21:19:41 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/04 16:02:29 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTIL_H
# define MLX_UTIL_H

# define LCLICK 1
# define RCLICK 2
# define MWHEELDN 4
# define MWHEELUP 5
# define MWHEELRT 6
# define MWHEELLF 7

# define MAX_BUTTONS 7

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_H 4
# define KEY_G 5
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_Y 16
# define KEY_T 17
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_6 22
# define KEY_5 23
# define PLUS 24
# define KEY_9 25
# define KEY_7 26
# define MINUS 27
# define KEY_8 28
# define KEY_0 29
# define CLOSE_BRACKET 30
# define KEY_O 31
# define KEY_U 32
# define OPEN_BRACKET 33
# define KEY_I 34
# define KEY_P 35
# define ENTER 36
# define KEY_L 37
# define KEY_J 38
# define APPOSTROPHE 39
# define KEY_K 40
# define SEMICOLON 41
# define BACKSLASH 42
# define COMMA 43
# define QUESTION_MARK 44
# define KEY_N 45
# define KEY_M 46
# define PERIOD 47
# define TAB 48
# define SPACE 49
# define TILDE 50
# define BACKSPACE 51
# define ESC 53

# define NUM_DOT 65
# define NUM_TIMES 67
# define NUM_PLUS 69
# define NUM_CLEAR 71
# define NUM_DIVIDE 75
# define NUM_ENTER 76
# define NUM_MINUS 78
# define NUM_EQUAL 81
# define NUM_0 82
# define NUM_1 83
# define NUM_2 84
# define NUM_3 85
# define NUM_4 86
# define NUM_5 87
# define NUM_6 88
# define NUM_7 89
# define NUM_8 91
# define NUM_9 92

# define HOME 115
# define PGUP 116
# define DELETE 117
# define END 119
# define PGDN 121

# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126

# define CTRL 256
# define SHIFT 257
# define RSHIFT 258
# define COMMAND 259
# define RCOMMAND 260
# define OPTION 261
# define ROPTION 262
# define RCTRL 269
# define CAPSLOCK 272
# define FN 279

# define MAX_KEYS 279

# define MLX void
# define MLX_WIN void
# define MLX_IMG void

typedef unsigned char	t_byte;

typedef struct	s_screen
{
	int			width;
	int			height;
	MLX			*mlx_ptr;
	MLX_WIN		*win_ptr;
	MLX_IMG		*img_ptr;
	t_byte		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_screen;

#endif
