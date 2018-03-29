def get_elment_value(strElement,tagname):
	strOpener="<" + tagname + ">"
	strCloser = "</" + tagname + ">"
	try:
		i = strElement.index(strOpener);
		start = i + len(strOpener)
		j = strElement.index(strCloser, start)
		return strElement[start:j]
	except ValueError as e:
		print(e)

def get_elment_value1(strElement,tagname):
	strOpener="<" + tagname + ">"
	strCloser = "</" + tagname + ">"
	i = strElement.find(strOpener)
	if i != -1:
		start = i + len(strOpener)
		j = strElement.find(strCloser,start);
		if j != -1:
			return strElement[start:j]
	return None

