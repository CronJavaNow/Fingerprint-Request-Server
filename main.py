import ssl
import json
import OpenSSL
from urllib.parse import urlparse, parse_qs
from http.server import BaseHTTPRequestHandler, HTTPServer


hostName = 'localhost'
serverPort = 8080


def server():
    web_server = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        web_server.serve_forever()
    except KeyboardInterrupt:
        pass

    web_server.server_close()
    print("Server stopped.")


def my_cert(site):
    cert = ssl.get_server_certificate((site, 443))
    x509 = OpenSSL.crypto.load_certificate(OpenSSL.crypto.FILETYPE_PEM, cert)
    sha1_fingerprint = x509.digest('sha1')
    return sha1_fingerprint.decode("utf-8")


class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'application/json')
        self.end_headers()
        query_components = parse_qs(urlparse(self.path).query)
        js = json.dumps({'finger_print': my_cert(str(query_components['site'][0]))})
        self.wfile.write(js.encode('utf-8'))


server()
