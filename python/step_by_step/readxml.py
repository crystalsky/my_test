from xml.dom.minidom import parse
import xml.dom.minidom
import os

def readxmlfile(xmlfile):
    domTree = xml.dom.minidom.parse(xmlfile)
    collection = domTree.documentElement
    if collection.hasAttribute("shelf"):
        print ("root Element: %s" % collection.getAttribute("shelf"))
    movies = collection.getElementsByTagName("movie")

    for movie in movies:
        if movie.hasAttribute("title"):
            print ("Title: %s" % movie.getAttribute("title"))

        type = movie.getElementsByTagName('type')[0]
        print ("Type: %s" % type.childNodes[0].data)
        format = movie.getElementsByTagName('format')[0]
        print ("Format: %s" % format.childNodes[0].data)
        rating = movie.getElementsByTagName('rating')[0]
        print ("Rating: %s" % rating.childNodes[0].data)
        description = movie.getElementsByTagName('description')[0]
        print ("Description: %s" % description.childNodes[0].data)


if ( __name__ == "__main__"):
    filePath = os.path.dirname(__file__) + "\\test1.xml"
    readxmlfile(filePath)
