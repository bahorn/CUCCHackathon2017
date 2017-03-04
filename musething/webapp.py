from flask import Flask, render_template, request, url_for

app = Flask(__name__)
@app.route("/", methods=['POST'])
def indexPage():
    print reques
    return ""

if __name__ == "__main__":
    app.run()
