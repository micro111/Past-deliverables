const Discord = require('discord.js');
const ytdl =require("ytdl-core");
const fs = require("fs");
const archiver = require('archiver');
const client = new Discord.Client();
const token = 'YOU RE Token';
const rl=require("readline");
require('date-utils');

var help="1.join    //参加  \n2.repeat　　//リピート\n3.read ファイル名   //ファイル読み込み\n4.url 動画  //動画追加\n5. write ファイル名 //ファイル書き込み\n6. rand  //ランダム再生\n\nstart　//一時停止解除\nstop   //一時停止\nnext //次の曲\nleave //落とす\n list //予約されている曲一覧を出すよ\n\n初期化したいときはrepeat ってのをもっかい入力してrepeatを切る→もっかいリピートにするとlistが空っぽになる";

var fname
let max=20; //list,restの最大
var list=[max]
var reli=[max]
var title=[max]//title
let now=0; //現在の再生
let st=0;rt=0; //曲保存
let count=1,rcount=1 ;//現在スタックのカウント
let repflag=0//rep or 通常
let rndflag=0//ランダム再生
var vc//voicechaannel
var dis; //dispatcher
var tmp;//message削除temp
let tout=5000;//消える時間(ms)
var dir="./test" //mp3でぃれ
var send=0;
client.on('ready',()=>{
  console.log('Ready!');
  //client.user.setUsername('MicroidMusicBot');
})

client.on('message',message=>{
  if(message.author.bot)return;
  if(message.content.match(/online/)){
    message.channel.send("online").then((msg)=>msg.delete({ timeout: tout }))
    client.user.setStatus('online').catch ( err => { console.log(err) } );
  }
  if(message.content.match(/offline/)){
    message.channel.send("offline").then((msg)=>msg.delete({ timeout: tout }))
    client.user.setStatus('invisible').catch ( err => { console.log(err) } );
  }
  if(message.content.match(/send/)){
    if(send==0){
      send=1;
      message.channel.send("send enabled").then((msg)=>msg.delete({ timeout: tout }))
    }else{
      send=0;
      message.channel.send("send disabled").then((msg)=>msg.delete({ timeout: tout }))
    }
  }
  if(message.content.match(/help/)){
    message.channel.send(help).then((msg)=>msg.delete({ timeout: 30000 }));
    console.log("help");
  }
  if(message.content.match(/start/)){
    message.channel.send("start").then((msg)=>msg.delete({ timeout: tout }))
    dis.resume()
  }

  if(message.content.match(/stop/)){
    message.channel.send("stop").then((msg)=>msg.delete({ timeout: tout }))
    dis.pause();
  }

  if(message.content.match(/join/)){
    res();
    message.channel.send("邪魔するぜ( ﾟДﾟ)").then(msg=>msg.delete({timeout:tout}));
    stmusic(message)
  }
  if(message.content.match(/tes/))message.channel.send("on");
  if(message.content.match(/邪魔す/)){
    if(message.member.voice.channel){
      message.channel.send("あいよー！( ﾟДﾟ)");
      message.member.voice.channel.leave()
    }
  }

  if(message.content.match(/leave/)){
    if(message.member.voice.channel){
      message.channel.send("またの( ﾟДﾟ)").then(msg=>msg.delete({timeout:tout}));
      message.member.voice.channel.leave()
    }else{
      message.channel.send("おぬし通話に参加してないじゃろう..( ﾟДﾟ)（ボイスチャンネルに参加してから使ってね。）").then(msg=>msg.delete({timeout:tout}));
    }
  }

  if(message.content.match(/next/)){
    nextmusic(message,nextmusic);
    tmp.delete();
  }

  if(message.content.match(/write/)){
    if(repflag==0){
      message.channel.send("書き込みはリピートモードの時可能です").then((msg)=>msg.delete({ timeout: tout }))
      console.log("書き込みはリピートモードの時可能です")
    }else{
      if(!message.content.split(" ")[1]){
        return;
      }
      wfile(message.content.split(" ")[1])
      message.channel.send("書き込みます:"+message.content.split(" ")[1]).then((msg)=>msg.delete({ timeout: tout }))
      console.log("書き込みます:"+message.content.split(" ")[1])
    }
  }


  if(message.content.match(/read/)){
    if(repflag==0){
      message.channel.send("読み込みはリピートモードの時可能です").then((msg)=>msg.delete({ timeout: tout }))
      console.log("読み込みはリピートモードの時可能です")
    }else{
      if(!message.content.split(" ")[1])return;
      rfile(message.content.split(" ")[1],message.channel)
    }
  }

  if(message.content.match(/alld/)){
    if(repflag==0){
      message.channel.send("DLはリピートモードの時可能です").then((msg)=>msg.delete({ timeout: tout }))
      console.log("DLはリピートモードの時可能です")
    }else{
      dlf()
      message.channel.send("DL..").then((msg)=>msg.delete({ timeout: tout }))
      console.log("DL..")
    }
  }
  if(message.content.match(/alls/)){
    if(repflag==0){
      message.channel.send("Sendはリピートモードの時可能です").then((msg)=>msg.delete({ timeout: tout }))
      console.log("Sendはリピートモードの時可能です")
    }else{
      sendlist(message);
      message.channel.send("send..").then((msg)=>msg.delete({ timeout: tout }))
      console.log("send..")
    }
  }


  if(message.content.match(/dl/)){
    let match = (message.content).match(/(?:^|[\s　]+)((?:https?|ftp):\/\/[^\s　]+)/);
    if (!match) return;
    dlp(match[1],message)
    message.channel.send("DL..").then((msg)=>msg.delete({ timeout: 50000 }))
    console.log("DL..")

  }



  if(message.content.match(/rand/)){
    if(repflag==0){
      message.channel.send("ランダム再生はリピートモードの時可能です").then((msg)=>msg.delete({ timeout: tout }))
      console.log("ランダム再生はリピートモードの時可能です")
    }else{
      if(rndflag==0){
        rndflag=1;
        message.channel.send("ランダム再生します").then((msg)=>msg.delete({ timeout: tout }))
        console.log("ランダム再生します")
      }else{
        rndflag=0;
        message.channel.send("ランダム再生を終わります").then((msg)=>msg.delete({ timeout: tout }))
        console.log("ランダム再生を終わります")
      }
    }
  }

  if(repflag==0){

    if(message.content.match(/url/)){
      let match = (message.content).match(/(?:^|[\s　]+)((?:https?|ftp):\/\/[^\s　]+)/);
      if (!match) return;
      list[st] = match[1];
      geti(list[st]).then(d=>{
        message.channel.send(count+"曲後に再生します。"+d).then((msg)=>msg.delete({ timeout: tout }))
        console.log(count+"曲後に再生します。"+d)
        title[st]=d;
        count++;
        if(st<max){st++}else{st=0};
      })
    }

    if(message.content.match(/repeat/)){
      message.channel.send("リピートモードをonにします。").then(msg=>msg.delete({ timeout: tout }))
      res();
      repflag=1;
    }

    if(message.content.match(/list/)){
      let index=0;
      while(!title[index])index++;
      index++;
      for(let i=1;i<count;i++,index++){
        console.log(title[index]);
        message.channel.send(i+":"+title[index]).then((msg)=>msg.delete({ timeout: tout }))
        if(index<max)index=0;
      }
    }

  }else{
    if(message.content.match(/url/)){
      console.log(rt)
      if(rt<max){
        let match = (message.content).match(/(?:^|[\s　]+)((?:https?|ftp):\/\/[^\s　]+)/);
        if (!match) return;
        reli[rt] = match[1];
        geti(reli[rt]).then(d=>{
          message.channel.send(rt+1+"曲目に再生します。(repeat)"+d).then((msg)=>msg.delete({ timeout: tout }))
          console.log(rt+1+"曲目に再生します。(repeat)"+d)
          title[rt]=d;
          rt++;
        })

      }else{
        message.channel.send(max+"曲以上は登録できません。").then((msg)=>msg.delete({ timeout: tout }))
        console.log(max+"曲以上は登録できません。")
      }
    }

    if(message.content.match(/rst/)){
      message.channel.send(rt+"曲でリピートします。").then((msg)=>msg.delete({ timeout: tout }))
      now--;
      nextmusic(message,nextmusic);
    }

    if(message.content.match(/repeat/)){
      message.channel.send("リピートモードをoffにします。").then(msg=>msg.delete({ timeout: tout }))
      res();
      repflag=0;
    }

    if(message.content.match(/list/)){
      for(let i=0;i<rt;i++){
        console.log(title[i]);
        message.channel.send(i+1+":"+title[i]).then((msg)=>msg.delete({ timeout: tout }))
      }
    }

  }


})

function stmusic(m){
  var ch=m.member.voice.channel;
  ch.join().then(conect=>{
    geti(list[0]).then(d=>{
      vc=conect
      title[0]=d
      client.user.setActivity(d, { type: "LISTENING" });
      m.channel.send("再生するぜ:"+d).then(temp=>tmp=temp)
      console.log("再生するぜ:"+d)
      dis=conect.play(ytdl(list[0], { filter: 'audioonly' }),{ volume: 0.2 })
      dis.once('finish',()=>{
        nextmusic(m,nextmusic)
        tmp.delete()
        count--;
      });
    })
  })
}

function nextmusic(m,callback){
  if(repflag==0){
    count--;
    list[now]="";
    title[now]="";
    if(now<max){now++}else{now=0};
    if(!list[now]){
      m.channel.send("曲がありません。曲を追加後/nextを入力してください。").then((msg)=>msg.delete({ timeout: tout }))
      now--;
      count++;
    }else{
      client.user.setActivity(title[now], { type: "LISTENING" });
      m.channel.send("再生するぜ:"+title[now]).then(temp=>tmp=temp)
      console.log("再生するぜ:"+title[now])
      dis = vc.play(ytdl(list[now], { filter: 'audioonly' }), { volume: 0.2 });
      dis.once('finish',()=>{
        nextmusic(m,nextmusic)
        tmp.delete()
      });
    }
  }else{
    if(rndflag==0){
      if(rt-1==now){now=0}else{now++};
    }else{
      now=Math.floor( Math.random() * rt)
    }
    if(!reli[now]){
      m.channel.send("曲がありません。曲を追加後/nextを入力してください。"+rt+":"+now).then((msg)=>msg.delete({ timeout: tout }))
    }else{
      console.log(now)
      client.user.setActivity(title[now], { type: "LISTENING" });
      m.channel.send("再生するぜ:"+title[now]).then(temp=>tmp=temp)
      console.log("再生するぜ:"+title[now])
      dis = vc.play(ytdl(reli[now], { filter: 'audioonly' }), { volume: 0.2 });
      dis.once('finish',()=>{
        nextmusic(m,nextmusic)
        tmp.delete()
      });
    }
  }
}

function res(){
  now=0; //現在の再生
  st=1;rt=0; //曲保存
  count=1;//現在スタックのカウント
  repflag=0//rep or 通常
  rndflag=0//ランダム再生
  list[0]="https://www.youtube.com/watch?v=BNdtdkObSP0"
  reli[0]="https://www.youtube.com/watch?v=BNdtdkObSP0"
}

async function geti(url){
  console.log(url);
  var res= await ytdl.getInfo(url)
  return res.videoDetails.title
}

async function rfile(fname,ch){
  if (fs.existsSync(fname+".txt")){
    ch.send("読み込みます:"+fname).then((msg)=>msg.delete({ timeout: tout }))
    console.log("読み込みます:"+fname);
    let index=0;
    rt=0;
    count=1;
    now=-1;
    var stream=fs.createReadStream(fname+".txt");
    var reads=rl.createInterface(stream,{});

    reads.on('line', (chunk) => {
      var temp=chunk.toString().split(",");
      reli[index]=temp[0];
      title[index]=temp[1];
      index++
      count++
      rt++
    })

    stream.on('end', () => {
      console.log("READ STRAM END");
      ch.send("読み込み終わりました。listで確認してください").then((msg)=>msg.delete({ timeout: tout }))
    })
  } else {
    console.log(fname+'ファイル・ディレクトリは存在しません。');
    ch.send("ファイル・ディレクトリは存在しません。").then((msg)=>msg.delete({ timeout: tout }))
  }
}

async function wfile(fname){
  var stream=fs.createWriteStream(fname+".txt");
  for(let i=0;i<rt;i++){
    console.log(i)
    stream.write(reli[i]+","+title[i]+"\n");
  }
  stream.end();
  stream.on('finish', () => {
    return "done"
  })
  stream.on("error", (err)=>{
    if(err)
    return err.message;
  });

}
function dlf(){
  var r=1;
  for(let i=0;i<rt;i++){
      var n=String(title[i]+".mp3");
      n=n.replace("/","●").replace(" /","●").replace(" ","●").replace("　","●").replace("-","●").replace("\"","").replace("\"","");
      n=dir+"/"+n;
    if (fs.existsSync(n)) {
        console.log("既にファイルが存在しています。");
        console.log('Download finish :'+n);
    } else {
    a(n,reli[i],r);
    r++;
  }
  }

}

function dlp(url,m){
  console.log(url)
  geti(url).then(tit=>{
    console.log(tit)
    b(tit,url,m);
  })
}

function a(name,url,i){
    setTimeout(()=>{
      console.log("start:"+name);
      video= ytdl(url,{quality: 140});
      video.on('error',err=>console.log(err));
      video.on('end', function(info) {
        console.log('Download finish :'+name)
      })
      video.pipe(fs.createWriteStream(name));
    },3000*i);
}

function b(name,url,message){
  var n=String(name+".mp3");
    n=n.replace("/","●").replace(" /","●").replace(" ","●").replace("　","●").replace("-","●").replace("\"","").replace("\"","");
  if (fs.existsSync(n)) {
    console.log("既にファイルが存在しています。")
    console.log('Download finish :'+name)
  } else {
    setTimeout(()=>{
      console.log("start:"+name);
      video= ytdl(url,{quality: 140});
      video.pipe(fs.createWriteStream(n));
      video.on('end', function(info) {
        console.log('Download finish :'+name)
        if(send==1){
          message.channel.send(name,{ files: [n]});
        }else{
          message.channel.send(name+":send diabled");
        }
        n.end();
      })
    },3000);
  }
}

function sendlist(message){
  var dt = new Date();
  var formatted = dt.toFormat("YYYYMMDDMI");
  var archive = archiver.create('zip', { zlib: { level: 9 } });
  var output = fs.createWriteStream(formatted+".zip");
  archive.pipe(output);
  for(let i=0;i<rt;i++){
    var n=String(title[i]);
    n=n.replace("/","●").replace(" /","●").replace(" ","●").replace("　","●").replace("-","●").replace("\"","").replace("\"","");
    var name=n;
    console.log(n);
    n=dir+"/"+n+".mp3";
    if (fs.existsSync(n)) {
      console.log(n);
      archive.file(n,{name:String(name+".mp3")});
    } else {
      console.log('ファイル・ディレクトリは存在しません。'+n);
    }
  }
  console.log("fi");
  output.on('end', function() {
    console.log('Data has been drained');
  });

  // good practice to catch warnings (ie stat failures and other non-blocking errors)
  archive.on('warning', function(err) {
    if (err.code === 'ENOENT') {
      // log warning
    } else {
      // throw error
      throw err;
    }
  });
  output.on("close", function () {
    // zip圧縮完了すると発火する
    output.end()
    message.channel.send("finish"+formatted+".zip");
  });
  archive.on('error', function(err) {
    throw err;
  });

  archive.on('warning', function(err) {
    if (err.code === 'ENOENT') {
      // log warning
    } else {
      // throw error
      throw err;
    }
  });
  archive.finalize().then(console.log("done"));
}

client.login(token)
