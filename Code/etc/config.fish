alias ra='ranger'
alias c='clear'
alias gad='git add'
alias gcm='git commit'
alias gst='git status'
alias glog='git reflog'
alias gco='git checkout'
alias gremote='git remote'
alias gbr='git branch'
alias vim='nvim'
alias copy='cp ~/.config/nvim/init.vim ~/gitRep/Code/etc/init.vim;cp ~/.config/ranger ~/gitRep/Code/etc/ranger -r;cp ~/.config/nvim/coc-settings.json ~/gitRep/Code/etc/coc-settings.json'

set -g -x RANGER_LOAD_DEFAULT_RC FALSE
export FZF_DEFAULT_COMMAND='ag --hidden --ignore .git -g ""'
