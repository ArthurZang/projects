"定义快捷键的前缀
let mapleader=";"

"开启文件类型侦测
filetype on
"根据文件类型加载插件
filetype plugin on

"定义快捷键到行尾和行头
nmap lb 0
nmap le $

"定义快捷键关闭当前分隔窗口
nmap <Leader>q :q<CR>

"定义快捷键保存当前窗口
nmap <leader>w :w<CR>

"定义快捷键保存所有窗口并退出
nmap <Leader>WQ :wa<CR>:q<CR>

"不保存，直接退出
nmap <Leader>Q :qa!<CR>

" 依次遍历子窗口
 nnoremap nw <C-W><C-W>

" 跳转至右方的窗口
 nnoremap <Leader>lw <C-W>l

" 跳转至左方的窗口
nnoremap <Leader>hw <C-W>h

" 跳转至上方的子窗口
nnoremap <Leader>kw <C-W>k

" 跳转至下方的子窗口
nnoremap <Leader>jw <C-W>j

" 定义快捷键在结对符之间跳转，助记pair
nmap <Leader>pa %

"开启实时搜索功能
set incsearch
"搜索时忽略大小写
set ignorecase
"关闭兼容模式
set nocompatible
"命令行自动补全
set wildmenu

"语法高亮
syntax enable

"语法缩进
filetype indent on

"制表符展开为空格
set expandtab

"制表符占4个空格
set tabstop=4

"连续4个空格为一个制表符
set shiftwidth=4

