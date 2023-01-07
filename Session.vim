let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Work/nigui_shell
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
set shortmess=aoO
badd +0 srcs/ft_exec.c
badd +14 srcs/ft_minishell.c
badd +0 srcs/ft_pipes.c
badd +0 srcs/ft_prompt.c
badd +18 niki_main.c
badd +19 srcs/ft_redirections.c
badd +75 srcs//ft_print.c
badd +55 includes/nikishell.h
badd +56 srcs/ft_fd.c
argglobal
%argdel
edit srcs/ft_prompt.c
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 35 + 37) / 74)
exe 'vert 1resize ' . ((&columns * 94 + 141) / 282)
exe '2resize ' . ((&lines * 36 + 37) / 74)
exe 'vert 2resize ' . ((&columns * 94 + 141) / 282)
exe 'vert 3resize ' . ((&columns * 93 + 141) / 282)
exe '4resize ' . ((&lines * 35 + 37) / 74)
exe 'vert 4resize ' . ((&columns * 93 + 141) / 282)
exe '5resize ' . ((&lines * 36 + 37) / 74)
exe 'vert 5resize ' . ((&columns * 93 + 141) / 282)
argglobal
balt srcs//ft_print.c
setlocal fdm=syntax
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=1
setlocal fen
4
normal! zc
13
normal! zc
23
normal! zc
let s:l = 49 - ((38 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 49
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("srcs//ft_print.c", ":p")) | buffer srcs//ft_print.c | else | edit srcs//ft_print.c | endif
if &buftype ==# 'terminal'
  silent file srcs//ft_print.c
endif
balt srcs/ft_prompt.c
setlocal fdm=syntax
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=1
setlocal fen
31
normal! zc
46
normal! zc
57
normal! zc
68
normal! zc
let s:l = 12 - ((11 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 12
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("srcs/ft_pipes.c", ":p")) | buffer srcs/ft_pipes.c | else | edit srcs/ft_pipes.c | endif
if &buftype ==# 'terminal'
  silent file srcs/ft_pipes.c
endif
setlocal fdm=syntax
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=1
setlocal fen
4
normal! zc
11
normal! zc
72
normal! zc
101
normal! zc
let s:l = 48 - ((47 * winheight(0) + 36) / 72)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 48
normal! 016|
wincmd w
argglobal
if bufexists(fnamemodify("srcs/ft_exec.c", ":p")) | buffer srcs/ft_exec.c | else | edit srcs/ft_exec.c | endif
if &buftype ==# 'terminal'
  silent file srcs/ft_exec.c
endif
balt includes/nikishell.h
setlocal fdm=syntax
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=1
setlocal fen
24
normal! zc
let s:l = 87 - ((29 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 87
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("includes/nikishell.h", ":p")) | buffer includes/nikishell.h | else | edit includes/nikishell.h | endif
if &buftype ==# 'terminal'
  silent file includes/nikishell.h
endif
balt srcs/ft_exec.c
setlocal fdm=syntax
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=99
setlocal fml=1
setlocal fdn=1
setlocal fen
let s:l = 50 - ((27 * winheight(0) + 18) / 36)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 50
normal! 033|
wincmd w
5wincmd w
exe '1resize ' . ((&lines * 35 + 37) / 74)
exe 'vert 1resize ' . ((&columns * 94 + 141) / 282)
exe '2resize ' . ((&lines * 36 + 37) / 74)
exe 'vert 2resize ' . ((&columns * 94 + 141) / 282)
exe 'vert 3resize ' . ((&columns * 93 + 141) / 282)
exe '4resize ' . ((&lines * 35 + 37) / 74)
exe 'vert 4resize ' . ((&columns * 93 + 141) / 282)
exe '5resize ' . ((&lines * 36 + 37) / 74)
exe 'vert 5resize ' . ((&columns * 93 + 141) / 282)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
