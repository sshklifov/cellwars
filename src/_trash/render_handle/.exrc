if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <C-Space> 
imap <Nul> <C-Space>
inoremap <expr> <Up> pumvisible() ? "\" : "\<Up>"
inoremap <expr> <S-Tab> pumvisible() ? "\" : "\<S-Tab>"
inoremap <expr> <Down> pumvisible() ? "\" : "\<Down>"
map! <S-Insert> <MiddleMouse>
nnoremap <silent>  :nohlsearch=has('diff')?'|diffupdate':''
vmap [% [%m'gv``
nnoremap \d :YcmShowDetailedDiagnostic
vmap ]% ]%m'gv``
vmap a% [%v]%
nmap cgc <Plug>ChangeCommentary
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
nmap gcu <Plug>Commentary<Plug>Commentary
nmap gcc <Plug>CommentaryLine
omap gc <Plug>Commentary
nmap gc <Plug>Commentary
xmap gc <Plug>Commentary
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
nmap <silent> <Plug>CommentaryUndo <Plug>Commentary<Plug>Commentary
map <S-Insert> <MiddleMouse>
inoremap <expr> 	 pumvisible() ? "\" : "\	"
inoremap  u
cabbr rename =getcmdpos() == 1 && getcmdtype() == ":" ? "Rename" : "rename"
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set autoread
set background=dark
set backspace=indent,eol,start
set cinoptions=g0,L0,l1
set complete=.,w,b,u,t
set completefunc=youcompleteme#Complete
set completeopt=menuone
set display=lastline
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set formatoptions=tcqj
set guifont=Monaco\ 10
set guitablabel=[%N]\ %t\ %M
set helplang=en
set history=1000
set incsearch
set laststatus=2
set listchars=tab:>\ ,trail:-,extends:>,precedes:<,nbsp:+
set mouse=a
set nrformats=bin,hex
set omnifunc=youcompleteme#OmniComplete
set operatorfunc=<SNR>19_go
set pyxversion=2
set ruler
set runtimepath=~/.vim,~/.vim/plugged/vim-sensible/,~/.vim/plugged/YouCompleteMe/,~/.vim/plugged/vim-commentary/,~/.vim/plugged/gruvbox/,~/.vim/plugged/rename.vim/,~/.vim/plugged/vim-glsl/,/usr/share/vim/vimfiles,/usr/share/vim/vim80,/usr/share/vim/vim80/pack/dist/opt/matchit,/usr/share/vim/vimfiles/after,~/.vim/plugged/vim-glsl/after,~/.vim/after
set scrolloff=1
set sessionoptions=blank,buffers,curdir,folds,help,tabpages,winsize
set shiftwidth=4
set shortmess=filnxtToOc
set sidescrolloff=5
set smarttab
set softtabstop=4
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc,.png,.jpg
set tabpagemax=50
set tags=./tags;,./TAGS,tags,TAGS
set termencoding=utf-8
set ttimeout
set ttimeoutlen=100
set updatetime=2000
set viminfo=!,'100,<50,s10,h
set wildignore=*.pyc
set wildmenu
set window=36
" vim: set ft=vim :
