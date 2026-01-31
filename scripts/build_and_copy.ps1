$ErrorActionPreference = 'Stop'
cmake --build build --config Debug
$src = Join-Path (Get-Location) 'build\src\Debug\sdl3_tutorial.exe'
$dstDir = Join-Path (Get-Location) 'build\Debug'
if (-not (Test-Path $dstDir)) {
    New-Item -ItemType Directory -Path $dstDir | Out-Null
}
if (Test-Path $src) {
    Copy-Item $src -Destination (Join-Path $dstDir (Split-Path $src -Leaf)) -Force
} else {
    Write-Host "Warning: executable not found: $src"
}
