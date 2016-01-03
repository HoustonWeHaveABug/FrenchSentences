#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/valid.h>

enum validate_e {
	VALIDATE_ERROR = -1,
	VALIDATE_KO = 0,
	VALIDATE_OK = 1
};
typedef enum validate_e validate_t;

validate_t validateXml(xmlDocPtr, const xmlChar *, int);

int main(int argc, char *argv[]) {
xmlDocPtr doc;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <XML file> <DTD file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	doc = xmlParseFile(argv[1]);
	if (!doc) {
		fprintf(stderr, "main: could not parse XML file\n");
		return EXIT_FAILURE;
	}
	if (validateXml(doc, (const xmlChar *)argv[2], 1) < VALIDATE_OK) {
		xmlFreeDoc(doc);
		return EXIT_FAILURE;
	}
	xmlFreeDoc(doc);
	return EXIT_SUCCESS;
}

validate_t validateXml(xmlDocPtr doc, const xmlChar *dtdFile, int displayErrors) {
validate_t r;
xmlDtdPtr dtd;
xmlValidCtxtPtr validCtxt;
	dtd = xmlParseDTD(NULL, dtdFile);
	if (!dtd) {
		fprintf(stderr, "validateXml: could not parse DTD file.\n");
		return VALIDATE_ERROR;
	}
	validCtxt = xmlNewValidCtxt();
	if (!validCtxt) {
		fprintf(stderr, "validateXml: could not create validation context.\n");
		xmlFreeDtd(dtd);
		return VALIDATE_ERROR;
	}
	if (displayErrors) {
		validCtxt->userData = stderr;
		validCtxt->error = (xmlValidityErrorFunc)fprintf;
		validCtxt->warning = (xmlValidityWarningFunc)fprintf;
	}
	r = xmlValidateDtd(validCtxt, doc, dtd);
	switch (r) {
	case VALIDATE_ERROR:
		fprintf(stderr, "validateXml: validation error.\n");
		break;
	case VALIDATE_KO:
		fprintf(stderr, "validateXml: invalid XML file.\n");
		break;
	case VALIDATE_OK:
		break;
	}
	xmlFreeValidCtxt(validCtxt);
	xmlFreeDtd(dtd);
	return r;
}
