from urllib2 import urlopen
import ssl, socket
import OpenSSL.crypto as crypto


def getCNSN(url):
  """
  param: url
  return:
    a list that contains [ CN, SN ]
  not_found if there is no CN or SN
  """

  to_return = ["not_found", "not_found"]

  # get rid of slash at the end of the URL
  if url.endswith("/"):
    url = url[:-1]

  if "http" in url:
    url = url.split("//")[1]

  url_with_http = "http://" + url

  # try open website and get SN from website.
  try:
    response = urlopen(url_with_http,
               context=ssl._create_unverified_context())
    to_return[1] = response.geturl().split("://", 1)[1].split('/', 1)[0]
  except:
    return to_return

  # There's no CN in http website
  if "https" in response.geturl():
    try:
      dst = (url, 443)
      s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      s.connect(dst)
      ctx = ssl.create_default_context()
      ctx.check_hostname = False
      ctx.verify_mode = ssl.CERT_NONE
      s = ctx.wrap_socket(s, server_hostname=dst[0])
      # get certificate
      cert_bin = s.getpeercert(True)
      x509 = crypto.load_certificate(crypto.FILETYPE_ASN1, cert_bin)
      to_return[0] = x509.get_subject().CN
    except:
      pass

  return to_return
