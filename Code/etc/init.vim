" __  __               _                    
"|  \/  |_   _  __   _(_)_ __ ___  _ __ ___ 
"| |\/| | | | | \ \ / / | '_ ` _ \| '__/ __|
"| |  | | |_| |  \ V /| | | | | | | | | (__ 
"|_|  |_|\__, |   \_/ |_|_| |_| |_|_|  \___|
"        |___/                              

let mapleader="\<space>" "指定leader = space
"       _             
" _ __ | |_   _  __ _ 
"| '_ \| | | | |/ _` |
"| |_) | | |_| | (_| |
"| .__/|_|\__,_|\__, |
"|_|            |___/ 
"
call plug#begin()
Plug 'easymotion/vim-easymotion'    "easymotion
Plug 'scrooloose/nerdtree'          "nerdtree
Plug 'tpope/vim-surround'           "vim-surround
Plug 'neoclide/coc.nvim',{'branch':'release'}   "coc.nvim
Plug 'mg979/vim-visual-multi', {'branch': 'master'}     "vim-multi-cursor
Plug 'jiangmiao/auto-pairs'         "自动括号补全
Plug 'rhysd/vim-clang-format'       "c代码格式化
"markdown
Plug 'vimwiki/vimwiki'              "markdown笔记管理
Plug 'iamcco/markdown-preview.nvim', { 'do': 'cd app && yarn install'  }
Plug 'dhruvasagar/vim-table-mode', { 'on': 'TableModeToggle' }  
call plug#end()

" _ __ ___   __ _ _ __  
"| '_ ` _ \ / _` | '_ \ 
"| | | | | | (_| | |_) |
"|_| |_| |_|\__,_| .__/ 
"                |_|    
map <C-z> <nop>
map <C-f> <nop>
noremap rf :r !figlet 
noremap <M-k> K
noremap <silent> <C-e> :NERDTreeToggle<CR>
noremap <M-F> :ClangFormat<CR>
noremap <C-l> gt
noremap <C-h> gT
noremap <C-\> :source init.vim<CR>

"normal
nnoremap <C-s> :w<CR>
nnoremap J 5j
nnoremap K 5k
nnoremap L $
nnoremap H ^
nnoremap yie ggyG
nnoremap die ggdG

"insert
inoremap jk <Esc>

"visual
vnoremap J 5j
vnoremap K 5k
vnoremap L $h
vnoremap H ^h


"                      _          _                     
" _ __ ___   __ _ _ __| | __   __| | _____      ___ __  
"| '_ ` _ \ / _` | '__| |/ /  / _` |/ _ \ \ /\ / / '_ \ 
"| | | | | | (_| | |  |   <  | (_| | (_) \ V  V /| | | |
"|_| |_| |_|\__,_|_|  |_|\_\  \__,_|\___/ \_/\_/ |_| |_|
"                                                       
map mp :call CompileRunGcc()<CR>
func! CompileRunGcc()
  exec "w"
  if &filetype == 'c'
    exec "!g++ % -o %<"
    exec "!time ./%<"
  elseif &filetype == 'cpp'
    exec "!g++ % -o %<"
    exec "!time ./%<"
  elseif &filetype == 'java'
    exec "!javac %"
    exec "!time java %<"
  elseif &filetype == 'sh'
    :!time bash %
  elseif &filetype == 'python'
    silent! exec "!clear"
    exec "!time python3 %"
  elseif &filetype == 'html'
    exec "!firefox % &"
  elseif &filetype == 'markdown'
    exec "MarkdownPreview"
  elseif &filetype == 'vimwiki'
    exec "MarkdownPreview"
  endif
endfunc

map MP :call CompileBuildrrr()<CR>
func! CompileBuildrrr()
  exec "w"
  if &filetype == 'vim'
    exec "source $MYVIMRC"
  elseif &filetype == 'markdown'
    exec "echo"
  endif
endfunc
"autocmd Filetype markdown map <leader>w yiWi[<esc>Ea](<esc>pa)
autocmd Filetype markdown inoremap ,f <Esc>/<++><CR>:nohlsearch<CR>c4l
autocmd Filetype markdown inoremap ,n ---<Enter><Enter>
autocmd Filetype markdown inoremap ,b **** <++><Esc>F*hi
autocmd Filetype markdown inoremap ,s ~~~~ <++><Esc>F~hi
autocmd Filetype markdown inoremap ,i ** <++><Esc>F*i
autocmd Filetype markdown inoremap ,d `` <++><Esc>F`i
autocmd Filetype markdown inoremap ,c ```<Enter><++><Enter>```<Enter><Enter><++><Esc>4kA
autocmd Filetype markdown inoremap ,h ====<Space><++><Esc>F=hi
autocmd Filetype markdown inoremap ,p ![](<++>) <++><Esc>F[a
autocmd Filetype markdown inoremap ,a [](<++>) <++><Esc>F[a
autocmd Filetype markdown inoremap ,1 #<Space><Enter><++><Esc>kA
autocmd Filetype markdown inoremap ,2 ##<Space><Enter><++><Esc>kA
autocmd Filetype markdown inoremap ,3 ###<Space><Enter><++><Esc>kA
autocmd Filetype markdown inoremap ,4 ####<Space><Enter><++><Esc>kA
autocmd Filetype markdown inoremap ,l --------<Enter>

let g:mkdp_auto_start = 0
let g:mkdp_auto_close = 1
let g:mkdp_refresh_slow = 0
let g:mkdp_command_for_global = 0
let g:mkdp_open_to_the_world = 0
let g:mkdp_open_ip = ''
let g:mkdp_browser = 'chromium'
let g:mkdp_echo_preview_url = 0
let g:mkdp_browserfunc = ''
let g:mkdp_preview_options = {
    \ 'mkit': {},
    \ 'katex': {},
    \ 'uml': {},
    \ 'maid': {},
    \ 'disable_sync_scroll': 0,
    \ 'sync_scroll_type': 'middle',
    \ 'hide_yaml_meta': 1
    \ }
let g:mkdp_markdown_css = ''
let g:mkdp_highlight_css = ''
let g:mkdp_port = ''
let g:mkdp_page_title = '「${name}」'

" _____                  __  __       _   _             
"| ____|__ _ ___ _   _  |  \/  | ___ | |_(_) ___  _ __  
"|  _| / _` / __| | | | | |\/| |/ _ \| __| |/ _ \| '_ \ 
"| |__| (_| \__ \ |_| | | |  | | (_) | |_| | (_) | | | |
"|_____\__,_|___/\__, | |_|  |_|\___/ \__|_|\___/|_| |_|
"                |___/                                  
"
let g:EasyMotion_ignorecase = 0
map  / <Plug>(easymotion-sn)
nmap <Leader>s <Plug>(easymotion-s)
"nmap <Leader>l <Plug>(easymotion-overwin-line)
"nmap <Leader>w <Plug>(easymotion-overwin-w)
"nmap <Leader>b <Plug>(easymotion-b)

"  ___ _   _ _ __ ___  ___  _ __ 
" / __| | | | '__/ __|/ _ \| '__|
"| (__| |_| | |  \__ \ (_) | |   
" \___|\__,_|_|  |___/\___/|_|   
                                
"使用0可以让光标在行头和行尾来回切换
noremap <expr>0 col(".")==1?"$":'0'
"再次打开文件时光标定位到上一次编辑的位置
au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif    
"不同模式下显示不同光标类型
let &t_SI = "\<Esc>]50;CursorShape=1\x7"
let &t_SR = "\<Esc>]50;CursorShape=2\x7"
let &t_EI = "\<Esc>]50;CursorShape=0\x7"


"                      _           
"  ___ ___   _____   _(_)_ __ ___  
" / __/ _ \ / __\ \ / / | '_ ` _ \ 
"| (_| (_) | (__ \ V /| | | | | | |
" \___\___/ \___(_)_/ |_|_| |_| |_|
"                                  
"let g:coc_global_extensions = ['coc-clangd', 'coc-json']
autocmd CursorHold * silent call CocActionAsync('highlight') "标记与光标所在单词相同的词语
set hidden                  "允许vim进行未保存时跳转至其他文件
set updatetime=100          "提高vim的运行速度
set shortmess+=c            "使补全列表更加精简
"查找上一个或下一个错误
nmap <silent> <Leader>[ <Plug>(coc-diagnostic-prev)
nmap <silent> <Leader>] <Plug>(coc-diagnostic-next)
"跳转到函数定义、类型定义、声明等等
nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references) 

"使左边的行号柱子更窄，信息更简洁精炼
"if has("nvim-0.5.0") || has("patch-8.1.1564")
"  set signcolumn=number
"else
"  set signcolumn=yes
"endif

"添加下面代码可以使coc.vim用tab键补全
inoremap <silent><expr> <TAB>
      \ pumvisible() ? "\<C-n>" :
      \ CheckBackspace() ? "\<TAB>" :
      \ coc#refresh()
inoremap <expr><S-TAB> pumvisible() ? "\<C-p>" : "\<C-h>"

function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction

"下面代码使的ctrl+space显示补全信息栏
if has('nvim')
  inoremap <silent><expr> <c-space> coc#refresh()
else
  inoremap <silent><expr> <c-@> coc#refresh()
endif

"让TAB直接补全列表中的第一项
inoremap <silent><expr> <CR> pumvisible() ? coc#_select_confirm()
                              \: "\<C-g>u\<CR>\<c-r>=coc#on_enter()\<CR>"

" GoTo code navigation.
nmap <silent> gd <Plug>(coc-definition)
nmap <silent> gy <Plug>(coc-type-definition)
nmap <silent> gi <Plug>(coc-implementation)
nmap <silent> gr <Plug>(coc-references)

"让alt+k显示当前光标所在处的对象帮助coc文档
nnoremap <silent> <M-k> :call ShowDocumentation()<CR>

function! ShowDocumentation()
  if CocAction('hasProvider', 'hover')
    call CocActionAsync('doHover')
  else
    call feedkeys('K', 'in')
  endif
endfunction

" Symbol renaming.重新定义变量名
nmap <leader>rn <Plug>(coc-rename)

" 格式化选中代码Formatting selected code.
"xmap <leader>f  <Plug>(coc-format-selected)
"nmap <leader>f  <Plug>(coc-format-selected)
"augroup mygroup
"autocmd!
"" Setup formatexpr specified filetype(s).
"autocmd FileType typescript,json setl formatexpr=CocAction('formatSelected')
"" Update signature help on jump placeholder.
"autocmd User CocJumpPlaceholder call CocActionAsync('showSignatureHelp')
"augroup end

" 对选中区域进行代码的动作 Applying codeAction to the selected region.
" Example: `<leader>aap` for current paragraph
xmap <leader>a  <Plug>(coc-codeaction-selected)
nmap <leader>a  <Plug>(coc-codeaction-selected)


"文件类型兼容
filetype on         
filetype indent on
filetype plugin on
filetype plugin indent on

"主题设置
"autocmd vimenter * ++nested colorscheme gruvbox

"          _   
" ___  ___| |_ 
"/ __|/ _ \ __|
"\__ \  __/ |_ 
"|___/\___|\__|
"              
"set list                   "显示行尾$符
syntax on                   "关键字高亮
set nocompatible            "版本兼容设置
set relativenumber          "设置相对行号
set nu                      "设置行号
set showcmd                 "显示命令，如3dd
set wildmenu                "显示命令行提示
set noignorecase            "查找时忽略区分大小写
"set smartcase               "查找时智能忽略大小写
set nohlsearch              "查找不会高亮显示
set wrap                    "超出终端显示范围时，跳转到下一行
set mouse=a                 "显示鼠标指针
set encoding=utf-8          "设置字符集为utf-8
set laststatus=2            "在窗口底部显示一个永久状态栏，文件名+行列号
set autochdir               "自动维护编辑的历史记录
set cursorline              "行光标
set scrolloff=5             "使光标距离窗口上下至少保留若干行，不会贴边
"缩进
set listchars=tab:>-,trail:-   "显示tab键
set tabstop=4               "一个tab相当于几个空格
set softtabstop=4           "按退格键时退回的缩进长度
set shiftwidth=4            "每一级缩进长度
set expandtab               "用空格符表示缩进
set autoindent              "创建新行时，使用与上一行同样的缩进
set smartindent
