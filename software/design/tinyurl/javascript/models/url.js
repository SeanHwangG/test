const mongoose = require("mongoose");

const urlSchema = new mongoose.Schema({
  url_id: String,
  longUrl: String,
  shortUrl: String,
  date: {type:String, default: Date.now}
})
module.exports = mongoose.model('url', urlSchema);