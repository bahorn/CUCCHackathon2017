from flask import Flask, request, render_template, send_from_directory
import redis


app = Flask(__name__, static_url_path='/static')

@app.route("/")
def index():
    r = redis.Redis()
    #keys = {"status":"","left":"","right":"","centerleft":"","centerright":""}
    allkeys = []
    allkeys += [r.hgetall("homepage:data")]
    keys = allkeys[0]
    return render_template("index.html", information=keys, data=allkeys)

@app.route("/givedata",methods=['post'])
def giveData():
    if request.cookies.get('auththing') == "notsecureatall":
        r = redis.Redis()
        r.hmset("homepage:data",{
            "status":request.form["status"],
            "left":request.form["left"],
            "right":request.form["right"],
            "centerleft":request.form["centerleft"],
            "centerright":request.form["centerright"],
            "left_sd":request.form["left_sd"], 
            "right_sd":request.form["right_sd"], 
            "centerleft_sd":request.form["centerleft_sd"], 
            "centerright_sd":request.form["centerright_sd"] 
            })
        return "thanks for data",
    else:
        return ""

if __name__ == "__main__":
    app.run()
