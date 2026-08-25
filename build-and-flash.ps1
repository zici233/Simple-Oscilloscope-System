$ErrorActionPreference = 'Stop'

$projectRoot = $PSScriptRoot
$cmakePath = 'C:\Users\28970\Toolchain\cmake-4.4.2-windows-x86_64\bin\cmake.exe'
$openOcdPath = 'C:\Users\28970\AppData\Local\Microsoft\WinGet\Packages\xpack-dev-tools.openocd-xpack_Microsoft.Winget.Source_8wekyb3d8bbwe\xpack-openocd-0.12.0-7\bin\openocd.exe'

# OpenOCD uses Tcl parsing, so use forward slashes and brace the ELF path.
$elfPath = (Join-Path $projectRoot 'build\debug\STM32RCT6.elf').Replace('\', '/')
$openOcdConfig = Join-Path $projectRoot 'openocd-stm32f1x.cfg'

Push-Location $projectRoot
try {
    & $cmakePath --build --preset debug
    if ($LASTEXITCODE -ne 0) {
        throw "CMake build failed (exit code $LASTEXITCODE)"
    }

    & $openOcdPath -f $openOcdConfig -c "program {$elfPath} verify reset exit"
    if ($LASTEXITCODE -ne 0) {
        throw "OpenOCD programming failed (exit code $LASTEXITCODE)"
    }
}
finally {
    Pop-Location
}
