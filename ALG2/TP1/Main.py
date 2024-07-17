import TextCompress as TextC
import sys

InputFile = ""
OutputFile = ""

if "-o" in sys.argv:
    OutIndex = sys.argv.index("-o") + 1
    OutputFile = sys.argv[OutIndex]

if "-c" in sys.argv:
    InIndex = sys.argv.index("-c") + 1
    InputFile = sys.argv[InIndex]

    if OutputFile == "":
        OutputFile = InputFile.split('.')[0] + ".z78"

    From = "Tests/"
    To = "Compressed/"

    InputFile = From + InputFile
    OutputFile = To + OutputFile

    TextC.CompressFile(InputFile, OutputFile)

if "-x" in sys.argv:
    InIndex = sys.argv.index("-x") + 1
    InputFile = sys.argv[InIndex]

    if OutputFile == "":
        OutputFile = InputFile.split('.')[0] + ".txt"

    From = "Compressed/"
    To = "Decompressed/"

    InputFile = From + InputFile
    OutputFile = To + OutputFile

    TextC.DecompressFile(InputFile, OutputFile)