$git_root = git.exe rev-parse --show-toplevel
Write-Output "GIT ROOT:" $git_root

Set-Location $git_root

[array] $unstaged_files = git.exe ls-files --modified --others --exclude-standard --full-name
[array] $files_to_format = $unstaged_files | Where-Object { $_ -match '\.(cpp|h|inl)$' } | ForEach-Object {Join-Path $git_root $_}

if ($files_to_format.Count -gt 0)
{
    Write-Output "FILES TO FORMAT:" $files_to_format
    $format_config = Join-Path $git_root ".clang-format"
    Write-Output ".CLANG-FORMAT:" $format_config
    clang-format.exe -i --style=file:$format_config $files_to_format
}
else
{
    Write-Output "NO FILE TO FORMAT"
}

Write-Output "DONE"
