git_root="$(git rev-parse --show-toplevel)"
echo "GIT ROOT:\n" $git_root

cd $git_root

files_to_format=$(git ls-files --modified --others --exclude-standard --full-name | grep -E '\.(cpp|h|inl)$' | xargs)

if [ -z "$files_to_format" ]; then
    echo "NO FILE TO FORMAT"
else
    echo "FILES TO FORMAT:\n" $files_to_format
    format_config="$git_root/.clang-format"
    echo ".CLANG-FORMAT:\n" $format_config
    clang-format -i --style=file:$format_config $files_to_format
fi

echo "DONE"
