import img2pdf
pdf_bytes = img2pdf.convert('test.jpg')

file = open("name.pdf","wb")
file.write(pdf_bytes)