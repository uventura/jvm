function CreateDirectories {
    param (
        [string[]]$directories
    )

    foreach ($directory in $directories) {
        if (-not (Test-Path $directory -PathType Container)) {
            New-Item -ItemType Directory -Path $directory | Out-Null
        }
    }
}

function CompileSourceFiles {
    param (
        [string[]]$sourceFiles
    )

    foreach ($file in $sourceFiles) {
        $outputFile = "obj\" + $file.Replace("src\", "").Replace(".c", ".o")
        $compileCommand = "gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -o $outputFile -c $file -Isrc"
        Invoke-Expression $compileCommand
    }
}

# Directories to create
$directories = @(
    "obj",
    "obj\lib\controller",
    "obj\lib\base\file",
    "obj\lib\base\structures",
    "obj\lib\base\math",
    "obj\lib\base\class_file",
    "obj\lib\interpreter",
    "obj\lib\class_loader",
    "obj\lib\class_loader\bootstrap",
    "obj\lib\runtime_data_area",
    "obj\lib\environment",
    "bin"
)

# Source files to compile
$sourceFiles = @(
    "src\main.c",
    "src\lib\controller\jvm_reader.c",
    "src\lib\controller\jvm_controller.c",
    "src\lib\controller\jvm_runner.c",
    "src\lib\base\file\read_bytes.c",
    "src\lib\base\structures\stack.c",
    "src\lib\base\math\iee754.c",
    "src\lib\base\class_file\class_defines.c",
    "src\lib\base\class_file\cp_info.c",
    "src\lib\interpreter\byte_code.c",
    "src\lib\interpreter\opcodes_generic.c",
    "src\lib\class_loader\class_file_list.c",
    "src\lib\class_loader\bootstrap\bootstrap.c",
    "src\lib\class_loader\class_loader.c",
    "src\lib\runtime_data_area\method_area.c",
    "src\lib\runtime_data_area\object.c",
    "src\lib\runtime_data_area\frame.c",
    "src\lib\environment\jvm_debug_functions.c"
)

# Create directories
CreateDirectories -directories $directories

# Compile source files
CompileSourceFiles -sourceFiles $sourceFiles

# Link object files
$objectFiles = Get-ChildItem "obj\*.o" -Recurse | ForEach-Object { $_.FullName }
Write-Output $objectFiles
$executable = "bin\jvm"
$linkCommand = "gcc -o $executable $objectFiles -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -O3 -Isrc"
Invoke-Expression $linkCommand
