from Trie import Trie
from math import ceil

def NumBytes(num):
    bits = bin(num)

    
    return ceil((len(bits) - 2)/8)

def CompressFile(input, output):
    f = open(input, "r")

    text = f.read()
    f.close()

    Dictionary = Trie()

    CompressedText = bytes("", "utf-8")

    string = ""

    for ch in text:
        string += ch

        if Dictionary.Search(string) == -1:
            Code = Dictionary.Insert(string)
            string = ""

            CodeBytes = NumBytes(Code)

            CompressedText += CodeBytes.to_bytes(1, "big") + Code.to_bytes(CodeBytes, "big") + bytes(ch, "utf-8")
    
    if(string != ""):
        Code = Dictionary.Search(string)
        CodeBytes = NumBytes(Code)

        CompressedText += CodeBytes.to_bytes(1, "big") + Code.to_bytes(CodeBytes, "big")


    o = open(output, "wb")

    o.write(CompressedText)
    o.close()

    

def DecompressFile(input, output):
    f = open(input, "rb")

    Dictionary = []
    text = ""

    Dictionary.append("")
    ChrNum = 1

    while ChrNum:
        CodeBytes = int.from_bytes(f.read(1), "big")
        Code = int.from_bytes(f.read(CodeBytes), "big")
        ch = f.read(1)
        ChrNum = int.from_bytes(ch, "big")

        if ChrNum in range(194, 223):
            ch += f.read(1)
        
        elif ChrNum in range(224, 239):
            ch += f.read(2)
        
        elif ChrNum in range(240, 247):
            ch += f.read(3)

        Dictionary.append(Dictionary[Code] + ch.decode("utf-8"))

    f.close()
    
    for string in Dictionary:
        text += string
    
    o = open(output, "w")

    o.write(text)
    o.close()