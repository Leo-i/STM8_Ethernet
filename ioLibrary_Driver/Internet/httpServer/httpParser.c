/**
 @file		httpd.c
 @brief 		functions associated http processing
 */

#include <stdio.h>
#include <string.h>
#include "socket.h"
#include "httpParser.h"

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
//uint8_t BUFPUB[2048];
uint8_t BUFPUB[256];

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void replacetochar(uint8_t * str, uint8_t oldchar, uint8_t newchar); 	/* Replace old character with new character in the string */
static uint8_t C2D(uint8_t c); 												/* Convert a character to HEX */

/**
 @brief	convert escape characters(%XX) to ASCII character
 url	- pointer to be converted ( escape characters )
 */ 
void unescape_http_url(char* url)
{
  int32_t x, y;

  for (x = 0, y = 0; url[y]; ++x, ++y)
  {
    if ((url[x] = url[y]) == '%')
    {
      url[x] = C2D(url[y + 1]) * 0x10 + C2D(url[y + 2]);
      y += 2;
    }
  }
  
  url[x] = '\0';
}


/**
 @brief	make response header such as html, gif, jpeg,etc.
 char * buf     - pointer to response header to be made
 char type      - response type 
 uint32_t len	- size of response header
 */ 
void make_http_response_head(char * buf, char type, uint32_t len)
{
  char* head;
  char tmp[10];
			
  /*  file type*/
  switch (type)
  {
  case PTYPE_HTML:
    head = RES_HTMLHEAD_OK;
    break;
  case PTYPE_GIF:
    head = RES_GIFHEAD_OK;
    break;
  case PTYPE_TEXT:
    head = RES_TEXTHEAD_OK;
    break;
  case PTYPE_JPEG:
    head = RES_JPEGHEAD_OK;
    break;
  case PTYPE_FLASH:
    head = RES_FLASHHEAD_OK;
    break;
  case PTYPE_XML:
    head =  RES_XMLHEAD_OK;
    break;
  case PTYPE_CSS:
    head = RES_CSSHEAD_OK;
    break;
  case PTYPE_JSON:
    head = RES_JSONHEAD_OK;
    break;
  case PTYPE_JS:
    head = RES_JSHEAD_OK;
    break;
  case PTYPE_CGI:
    head = RES_CGIHEAD_OK;
    break;
  case PTYPE_PNG:
    head = RES_PNGHEAD_OK;
    break;
  case PTYPE_ICO:
    head = RES_ICOHEAD_OK;
    break;
  case PTYPE_TTF:
    head = RES_TTFHEAD_OK;
    break;
  case PTYPE_OTF:
    head = RES_OTFHEAD_OK;
    break;
  case PTYPE_WOFF:
    head = RES_WOFFHEAD_OK;
    break;
  case PTYPE_EOT:
    head = RES_EOTHEAD_OK;
    break;
  case PTYPE_SVG:
    head = RES_SVGHEAD_OK;
    break;
  default:
    head = NULL;
#ifdef _HTTPPARSER_DEBUG_
    printf("\r\n\r\n-MAKE HEAD UNKNOWN-\r\n");
#endif	
    break;
  }

  sprintf(tmp, "%ld", len);
  strcpy(buf, head);
  strcat(buf, tmp);
  strcat(buf, "\r\n\r\n");
}


/**
 @brief	find MIME type of a file
 uint8_t * type         - type to be returned
 uint8_t * buff		- file name
 */ 
void find_http_uri_type(uint8_t * type,	uint8_t * buff) 
{
  /* Decide type according to extension*/
  char * buf;
  buf = (char *)buff;

  if (strstr(buf, ".htm") || strstr(buf, ".html"))
    *type = PTYPE_HTML;
  else if (strstr(buf, ".gif"))
    *type = PTYPE_GIF;
  else if (strstr(buf, ".text") || strstr(buf,".txt"))
    *type = PTYPE_TEXT;
  else if (strstr(buf, ".jpeg") || strstr(buf,".jpg"))
    *type = PTYPE_JPEG;
  else if (strstr(buf, ".swf"))
    *type = PTYPE_FLASH;
  else if (strstr(buf, ".cgi") || strstr(buf,".CGI"))
    *type = PTYPE_CGI;
  else if (strstr(buf, ".json") || strstr(buf,".JSON"))
    *type = PTYPE_JSON;
  else if (strstr(buf, ".js") || strstr(buf,".JS"))
    *type = PTYPE_JS;
  else if (strstr(buf, ".CGI") || strstr(buf,".cgi"))
    *type = PTYPE_CGI;
  else if (strstr(buf, ".xml") || strstr(buf,".XML"))
    *type = PTYPE_XML;
  else if (strstr(buf, ".css") || strstr(buf,".CSS"))
    *type = PTYPE_CSS;
  else if (strstr(buf, ".png") || strstr(buf,".PNG"))
    *type = PTYPE_PNG;
  else if (strstr(buf, ".ico") || strstr(buf,".ICO"))
    *type = PTYPE_ICO;
  else if (strstr(buf, ".ttf") || strstr(buf,".TTF"))
    *type = PTYPE_TTF;
  else if (strstr(buf, ".otf") || strstr(buf,".OTF"))
    *type = PTYPE_OTF;
  else if (strstr(buf, ".woff") || strstr(buf,".WOFF"))
    *type = PTYPE_WOFF;
  else if (strstr(buf, ".eot") || strstr(buf,".EOT"))
    *type = PTYPE_EOT;
  else if (strstr(buf, ".svg") || strstr(buf,".SVG"))
    *type = PTYPE_SVG;
  else
    *type = PTYPE_ERR;
}


/**
 @brief	parse http request from a peer
 st_http_request * request      - request to be returned
 uint8_t * buf			- pointer to be parsed
 */ 
void parse_http_request(st_http_request * request, uint8_t * buf)
{
  char * nexttok;
  nexttok = strtok((char*)buf, " ");
  
  if (!nexttok)
  {
    request->METHOD = METHOD_ERR;
    return;
  }
  
  if (!strcmp(nexttok, "GET") || !strcmp(nexttok, "get"))
  {
    request->METHOD = METHOD_GET;
    nexttok = strtok(NULL, " ");
  }
  else if (!strcmp(nexttok, "HEAD") || !strcmp(nexttok, "head"))
  {
    request->METHOD = METHOD_HEAD;
    nexttok = strtok(NULL, " ");
  }
  else if (!strcmp(nexttok, "POST") || !strcmp(nexttok, "post"))
  {
    nexttok = strtok(NULL, "\0");
    request->METHOD = METHOD_POST;
  }
  else
    request->METHOD = METHOD_ERR;

  if (!nexttok)
  {
    request->METHOD = METHOD_ERR;
    return;
  }
  strcpy((char *)request->URI, nexttok);
}

#ifdef _OLD_
/**
 @brief	get next parameter value in the request
 */
uint8_t * get_http_param_value(char* uri, char* param_name)
{
  char tempURI[MAX_URI_SIZE];
  uint8_t * name = 0;
	
  if (!uri || !param_name)
    return 0;
	
  strcpy((char*)tempURI, uri);
  
  if ((name = (uint8_t*)strstr(tempURI, param_name)))
  {
    name += strlen(param_name) + 1; // strlen(para_name) + strlen("=")
    if ((name = (uint8_t*)strtok((char *)name,"& \r\n\t\0")))
    {
      unescape_http_url((char *)name);
      replacetochar(name, '+', ' ');
    }
  }
#ifdef _HTTPPARSER_DEBUG_
  printf("  %s=%s",param_name,name);
#endif	

  return name;
}

#else

/**
 @brief	get next parameter value in the request
 */
uint8_t * get_http_param_value(char* uri, char* param_name)
{
  uint8_t * name = 0;
  uint8_t * ret = BUFPUB;
  uint8_t * pos2;
  uint16_t len = 0, content_len = 0;
  uint8_t tmp_buf[10] = {0x00, };

  if (!uri || !param_name)
    return 0;

  /***************/
  mid(uri, "Content-Length: ", "\r\n", (char *)tmp_buf);
  content_len = ATOI(tmp_buf, 10);
  uri = strstr(uri, "\r\n\r\n");
  uri += 4;
  uri[content_len] = 0;
  /***************/

  if ((name = (uint8_t *)strstr(uri, param_name)))
  {
    name += strlen(param_name) + 1;
    pos2 = (uint8_t*)strstr((char*)name, "&");
    
    if (!pos2)
      pos2 = name + strlen((char*)name);
    
    len = pos2 - name;

    if (len)
    {
      ret[len] = 0;
      strncpy((char*)ret, (char*)name, len);
      unescape_http_url((char *)ret);
      replacetochar(ret, '+', ' ');
      //ret[len] = 0;
      //ret[strlen((int8*)ret)] = 0;
      //printf("len=%d\r\n",len);
    }
    else
      ret[0] = 0;
  }
  else
    return 0;

#ifdef _HTTPPARSER_DEBUG_
  printf("  %s=%s\r\n", param_name, ret);
#endif
  
  return ret;
}
#endif

#ifdef _OLD_
uint8_t * get_http_uri_name(uint8_t * uri)
{
  char tempURI[MAX_URI_SIZE];
  uint8_t * uri_name;

  if (!uri)
    return 0;

  strcpy(tempURI, (char *)uri);
  uri_name = (uint8_t *)strtok(tempURI, " ?");

  if (strcmp((char *)uri_name, "/"))
    uri_name++;

#ifdef _HTTPPARSER_DEBUG_
  printf("  uri_name = %s\r\n", uri_name);
#endif	

  return uri_name;
}
#else

uint8_t get_http_uri_name(uint8_t * uri, uint8_t * uri_buf)
{
  uint8_t * uri_ptr;
  
  if (!uri)
    return 0;

  strcpy((char *)uri_buf, (char *)uri);
  uri_ptr = (uint8_t *)strtok((char *)uri_buf, " ?");

  if (strcmp((char *)uri_ptr, "/"))
    uri_ptr++;

  strcpy((char *)uri_buf, (char *)uri_ptr);

#ifdef _HTTPPARSER_DEBUG_
  printf("  uri_name = %s\r\n", uri_buf);
#endif

  return 1;
}
#endif

void inet_addr_(uint8_t * addr, uint8_t *ip)
{
  uint8_t i;
  uint8_t taddr[30];
  uint8_t* nexttok;
  uint8_t num;

  strcpy((char *)taddr, (char *)addr);

  nexttok = taddr;

  for (i = 0; i < 4 ; i++)
  {
    nexttok = (uint8_t *)strtok((char *)nexttok, ".");
    
    if (nexttok[0] == '0' && nexttok[1] == 'x')
      num = ATOI(nexttok + 2, 0x10);
    else
      num = ATOI(nexttok, 10);
    
    ip[i] = num;
    nexttok = NULL;
  }
}


/**
 @brief	CONVERT STRING INTO INTEGER
 @return	a integer number
 uint8_t * str, - is a pointer to convert
 uint8_t base   - is a base value (must be in the range 2 - 16)
*/
uint16_t ATOI(uint8_t* str, uint8_t base)
{
  uint32_t num = 0;
  
// debug_2013_11_25
//        while (*str !=0)

  while ((*str !=0) && (*str != 0x20)) // not include the space(0x020)
    num = num * base + C2D(*str++);

  return num;
}

/**
 * @brief Check strings and then execute callback function by each string.
 * @param src The information of URI
 * @param s1 The start string to be researched
 * @param s2 The end string to be researched
 * @param sub The string between s1 and s2
 * @return The length value atfer working
 */
void mid(char* src, char* s1, char* s2, char* sub)
{
  char* sub1;
  char* sub2;
  uint16_t n;

  sub1 = strstr((char*)src, (char*)s1);
  sub1 += strlen((char*)s1);
  sub2 = strstr((char*)sub1, (char*)s2);

  n = sub2 - sub1;
  strncpy((char*)sub, (char*)sub1, n);
  sub[n] = '\0';
}

/**
 @brief	replace the specified character in a string with new character
 uint8_t * str          - pointer to be replaced
 uint8_t oldchar        - old character
 uint8_t newchar        - new character
*/
static void replacetochar(uint8_t* str,	uint8_t oldchar, uint8_t newchar)
{
  for (int32_t x = 0; str[x]; x++)
  {
    if (str[x] == oldchar)
      str[x] = newchar;
  }
}

/**
 @brief	CONVERT CHAR INTO HEX
 @return	HEX
 This function converts HEX(0-F) to a character
 uint8_t c	- is a character('0'-'F') to convert to HEX
*/
static uint8_t C2D(uint8_t c)
{
  if (c >= '0' && c <= '9')
    return c - '0';
  
  if (c >= 'a' && c <= 'f')
    return 10 + c -'a';

  if (c >= 'A' && c <= 'F')
    return 10 + c -'A';

  return (char)c;
}
