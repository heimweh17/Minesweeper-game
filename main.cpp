#include <SFML/Graphics.hpp>
#include <iostream>
#include<cctype>
#include<fstream>
#include <random>
#include<map>
#include <ctime>
#include <chrono>
#include <iomanip>


using namespace std;
using namespace sf;
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}
struct pntbtr{
    int m=0;
    int a=0;
    int b=0;
    int count=0;
    int flag=0;
};
struct score{
    int sec;
    string name;
};
void revc(vector<vector<pntbtr>>& c,vector<vector<Sprite>>& d,int a, int b,const Texture& rev,Texture numshow[],int a12,int b12,vector<vector<Sprite>>& g2){
    if(a<0||a>=b12||b<0||b>=a12){
        return;
    }
    if(c[a][b].a==1||c[a][b].flag==1)
    {
        return;
    }
    if(a>=0&&a<b12&&b>=0&&b<a12){
        if(c[a][b].count==0){
            c[a][b].a=1;
            d[a][b].setTexture(rev);
            revc(c,d,a+1,b,rev,numshow,a12,b12,g2);
            revc(c,d,a,b+1,rev,numshow,a12,b12,g2);
            revc(c,d,a-1,b,rev,numshow,a12,b12,g2);
            revc(c,d,a,b-1,rev,numshow,a12,b12,g2);
            revc(c,d,a+1,b+1,rev,numshow,a12,b12,g2);
            revc(c,d,a+1,b-1,rev,numshow,a12,b12,g2);
            revc(c,d,a-1,b+1,rev,numshow,a12,b12,g2);
            revc(c,d,a-1,b-1,rev,numshow,a12,b12,g2);
        }
        else{
            c[a][b].a=1;
            d[a][b].setTexture(numshow[c[a][b].count]);
            g2[a][b].setTexture(rev);
        }
    }
    else{
        return;
    }

}

int main(){
    int ts1,ts2,ts3,ts4,time0,time00,timenow;
    int sto=0;
    int stoo=0;
    int worl=0;
    int lbp=0;
    ifstream cfile("files/config.cfg");
    int a12,b12,c12;
    if (!cfile.is_open()) {
        cout<<"cant open cconfig "<<endl;
        return 0;
    }
    int al5;
    al5=0;
    string bl5;
    /*while(getline(cfile,bl5)){

    }*/
    cfile>>a12>>b12>>c12;
    RenderWindow window(sf::VideoMode(a12*32, b12*32+100), "Welcome Window");
    Font font;
    Texture numshow[9];
    Texture flag;
    flag.loadFromFile("files/images/flag.png");
    Texture hid;

    hid.loadFromFile("files/images/tile_hidden.png");
    Texture rev, mine;
    rev.loadFromFile("files/images/tile_revealed.png");
    mine.loadFromFile("files/images/mine.png");
    int i19;
    for(i19=1;i19<9;i19++){
        numshow[i19].loadFromFile("files/images/number_"+to_string(i19)+".png");
    }
    font.loadFromFile("files/font.ttf");
    Text welsen("WELCOME TO MINESWEEPER!",font,24);
    Texture fa1,fa2,fa3;
    fa1.loadFromFile("files/images/face_happy.png");
    fa2.loadFromFile("files/images/face_win.png");
    fa3.loadFromFile("files/images/face_lose.png");
    Texture debg;
    debg.loadFromFile("files/images/debug.png");
    Texture sorp;
    sorp.loadFromFile("files/images/pause.png");
    Texture sorp2;
    sorp2.loadFromFile("files/images/play.png");
    Sprite sop(sorp);
    sop.setPosition((a12*32)-240,b12*32+18);
    Texture leeeed;
    leeeed.loadFromFile("files/images/leaderboard.png");
    Sprite led(leeeed);
    led.setPosition((a12*32)-176,b12*32+18);
    welsen.setFillColor(Color::White);
    welsen.setStyle(Text::Underlined);
    string name;
    int ssave=0;
    Text ena("Enter your name:",font,20);
    ena.setFillColor(Color::White);
    Text ite("", font, 18);
    ite.setFillColor(Color::Yellow);
    Text cursor("|", font, 18);
    cursor.setFillColor(Color::Yellow);
    Sprite face(fa1);
    face.setPosition((a12*32)/2-32,b12*32+18);
    Sprite dbg(debg);
    dbg.setPosition((a12*32)-304,b12*32+18);
    int iamdbg=0;
    int tst=0;
    int tbp=0;
    int res=0;
    int lb=0;

    auto btime=chrono::system_clock::now();
    auto etime=chrono::system_clock::now();
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type==Event::Closed){
                window.close();
            }
            if (event.type==Event::TextEntered) {
                char c=static_cast<char>(event.text.unicode);
                if (isalpha(c)) {
                    if(name.length()==0){
                        name=name+static_cast<char>(toupper(c));
                    }
                    else{
                        if(name.length()<10){
                            name=name+static_cast<char>(tolower(c));
                        }
                    }
                }
                ite.setString(name);
            }
            if (event.type==Event::KeyPressed&&event.key.code == sf::Keyboard::Backspace){
                if(name.length()!=0){
                    name.pop_back();
                }
            }
            if (event.type==Event::KeyPressed&&event.key.code==Keyboard::Enter){
                if(name.length()!=0){
                    //cout << "enterning game window "<<endl;
                    window.close();
                    //cfile.close();

                    RenderWindow w2(sf::VideoMode(a12*32, b12*32+100), "Gaming Window");
                    Sprite digitss[10];
                    int i0,i1;
                    Texture dig;
                    dig.loadFromFile("files/images/digits.png");
                    for (i0=0;i0<10;i0++) {
                        digitss[i0].setTexture(dig);
                        digitss[i0].setTextureRect(IntRect(i0*21,0,21,32));
                    }
                    Sprite minus0;
                    minus0.setTexture(dig);
                    minus0.setTextureRect(IntRect(10 * 21, 0, 21, 32));
                    bool ib0=true;
                    //Texture number
                    vector<vector<Sprite>> g0(b12, vector<Sprite>(a12));
                    vector<vector<pntbtr>> g1(b12, vector<pntbtr>(a12));
                    vector<vector<Sprite>> g2(b12, vector<Sprite>(a12));
                    vector<vector<Sprite>> g3(b12, vector<Sprite>(a12));

                    for(i0=0;i0<b12;i0++) {
                        for(i1= 0;i1<a12;i1++) {
                            g0[i0][i1].setPosition(i1*32,i0*32);
                            g0[i0][i1].setTexture(hid);
                            g2[i0][i1].setPosition(i1*32,i0*32);
                            g2[i0][i1].setTexture(rev);
                            g3[i0][i1].setPosition(i1*32,i0*32);
                            g3[i0][i1].setTexture(rev);
                        }
                    }
                    srand(time(0));
                    //map<int,int> numalrsel;
                    for(i0=0;i0<c12;i0++){
                        int rnumb=0+(rand()%(b12));
                        int rnuma=0+(rand()%(a12));
                        if(g1[rnumb][rnuma].m==1){
                            i0--;
                            continue;
                        }
                        else{
                            g1[rnumb][rnuma].m=1;
                        }
                    }
                    int countofmine=c12;
                    for(i0=0;i0<b12;i0++){
                        for(i1=0;i1<a12;i1++){
                            int cnt=0;
                            for(int k0=-1;k0<2;k0++){
                                for(int k1=-1;k1<2;k1++){
                                    if(k0!=0||k1!=0){
                                        int nr12=i0+k0;
                                        int nc12=i1+k1;
                                        if(nr12>=0&&nr12<b12&&nc12>=0&&nc12<a12){
                                            if(g1[nr12][nc12].m){
                                                cnt++;
                                            }
                                        }
                                    }
                                }
                            }
                            g1[i0][i1].count=cnt;
                        }
                    }
                    auto st0=chrono::system_clock::now();
                    //auto timeinlb=chrono::system_clock::now();

                    while(w2.isOpen()){
                        Text welg("WELCOME TO GAMINGWINDOW!",font,24);
                        Text com(to_string(countofmine),font,21);

                        while (w2.pollEvent(event)) {
                            if (event.type==Event::Closed){
                                w2.close();
                            }
                            if (event.type==Event::MouseButtonPressed&&event.mouseButton.button==Mouse::Right){
                                int wx=event.mouseButton.x/32;
                                int wy=event.mouseButton.y/32;

                                if(ib0&&lb==0&&wx<a12&&wx>=0&&worl==0&&sto==0){
                                    if(wy<b12&&wy>=0) {
                                        if(g1[wy][wx].flag==0&&g1[wy][wx].a==0){
                                            g1[wy][wx].flag=1;
                                            g0[wy][wx].setTexture(flag);
                                            g2[wy][wx].setTexture(hid);
                                            countofmine--;
                                        }
                                        else if(g1[wy][wx].flag==1){
                                            g1[wy][wx].flag=0;
                                            if(iamdbg==0){
                                                g0[wy][wx].setTexture(hid);
                                                g2[wy][wx].setTexture(rev);
                                            }
                                            else if(iamdbg==1){
                                                if(g1[wy][wx].m==1){
                                                    g2[wy][wx].setTexture(hid);
                                                    g0[wy][wx].setTexture(mine);
                                                }
                                                else{
                                                    g0[wy][wx].setTexture(hid);
                                                    g2[wy][wx].setTexture(rev);
                                                }
                                            }
                                            //g2[wy][wx].setTexture(rev);
                                            countofmine++;
                                        }
                                    }

                                }
                                com.setString(to_string(countofmine));
                            }
                            if (event.type==Event::MouseButtonPressed&&event.mouseButton.button==Mouse::Left){
                                int wx=event.mouseButton.x/32;
                                int wy=event.mouseButton.y/32;

                                if(lb==0&&wx<a12&&wx>=0&&wy<b12&&wy>=0&&g1[wy][wx].flag==0&&worl==0&&sto==0){
                                    //cout<<sto<<endl;
                                    if(g1[wy][wx].a==0){
                                        //g1[wy][wx].a=1;
                                        if(g1[wy][wx].m==1){
                                            g0[wy][wx].setTexture(mine);
                                            g1[wy][wx].a=1;
                                        }
                                        else{
                                            if(g1[wy][wx].count==0){
                                                //g0[wy][wx].setTexture(rev);
                                                //g1[wy][wx].a=1;
                                                revc(g1,g0,wy,wx,rev,numshow,a12,b12,g2);
                                                //cout << g0[wy][wx].getTexture() << "second\n";

                                            }
                                            else
                                            {
                                                //Texture ncountm;
                                                //ncountm.loadFromFile("files/images/number_"+to_string(g1[wy][wx].count)+".png");
                                                g0[wy][wx].setTexture(numshow[g1[wy][wx].count]);
                                                g1[wy][wx].a=1;
                                                g2[wy][wx].setTexture(rev);
                                            }
                                        }

                                    }

                                }
                                else{
                                    //cout<<"hello";
                                    if(lb==0&&event.mouseButton.x>=face.getPosition().x&&event.mouseButton.x<face.getPosition().x+face.getGlobalBounds().width&&event.mouseButton.y>=face.getPosition().y&&event.mouseButton.y<face.getPosition().y+face.getGlobalBounds().height){
                                        worl=0;
                                        ssave=0;
                                        iamdbg=0;
                                        if(sto==1){
                                            res=1;
                                        }
                                            //cout<<"stopandgo"<<endl;
                                        else{
                                            st0=chrono::system_clock::now();
                                        }
                                        sto=0;
                                        stoo=0;
                                        res=0;
                                        tbp=0;
                                        st0=chrono::system_clock::now();
                                        tst=0;
                                        //cout<<"hit"<<wx*32<<wy*32<<endl;
                                        for(i0=0;i0<b12;i0++){
                                            for(i1=0;i1<a12;i1++){
                                                g1[i0][i1].a=0;
                                                g1[i0][i1].flag=0;
                                                g1[i0][i1].count=0;
                                                g1[i0][i1].m=0;
                                                g0[i0][i1].setTexture(hid);
                                            }
                                        }
                                        for(i0=0;i0<b12;i0++) {
                                            for(i1= 0;i1<a12;i1++) {
                                                g0[i0][i1].setPosition(i1*32,i0*32);
                                                g0[i0][i1].setTexture(hid);
                                            }
                                        }
                                        srand(time(0));
                                        //map<int,int> numalrsel;
                                        for(i0=0;i0<c12;i0++){
                                            int rnumb=0+(rand()%(b12));
                                            int rnuma=0+(rand()%(a12));
                                            if(g1[rnumb][rnuma].m==1){
                                                i0--;
                                                continue;
                                            }
                                            else{
                                                g1[rnumb][rnuma].m=1;
                                            }
                                        }
                                        countofmine=c12;
                                        for(i0=0;i0<b12;i0++){
                                            for(i1=0;i1<a12;i1++){
                                                int cnt=0;
                                                for(int k0=-1;k0<2;k0++){
                                                    for(int k1=-1;k1<2;k1++){
                                                        if(k0!=0||k1!=0){
                                                            int nr12=i0+k0;
                                                            int nc12=i1+k1;
                                                            if(nr12>=0&&nr12<b12&&nc12>=0&&nc12<a12){
                                                                if(g1[nr12][nc12].m){
                                                                    cnt++;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                g1[i0][i1].count=cnt;
                                            }
                                        }

                                    }
                                    else if(lb==0&&sto==0&&worl==0&&event.mouseButton.x>=dbg.getPosition().x&&event.mouseButton.x<dbg.getPosition().x+dbg.getGlobalBounds().width&&event.mouseButton.y>=dbg.getPosition().y&&event.mouseButton.y<dbg.getPosition().y+dbg.getGlobalBounds().height){
                                        if(iamdbg==0){
                                            iamdbg=1;
                                            for(i0=0;i0<b12;i0++) {
                                                for (i1 = 0; i1 < a12; i1++) {
                                                    if(g1[i0][i1].m==1){
                                                        g2[i0][i1].setTexture(hid);
                                                        g0[i0][i1].setTexture(mine);
                                                    }
                                                }
                                            }
                                        }
                                        else if(iamdbg==1){
                                            iamdbg=0;
                                            for(i0=0;i0<b12;i0++) {
                                                for (i1 = 0; i1 < a12; i1++) {
                                                    if(g1[i0][i1].m==1&&g1[i0][i1].flag==0){
                                                        g2[i0][i1].setTexture(rev);
                                                        g0[i0][i1].setTexture(hid);
                                                    }
                                                    else if(g1[i0][i1].m==1&&g1[i0][i1].flag==1){
                                                        g2[i0][i1].setTexture(rev);
                                                        g0[i0][i1].setTexture(flag);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else if(lb==0&&worl==0&&event.mouseButton.x>=sop.getPosition().x&&event.mouseButton.x<sop.getPosition().x+sop.getGlobalBounds().width&&event.mouseButton.y>=sop.getPosition().y&&event.mouseButton.y<sop.getPosition().y+sop.getGlobalBounds().height){
                                        //cout<<"sopbeenclicked"<<endl;
                                        if(sto==0){
                                            sto=1;
                                            sop.setTexture(sorp2);
                                        }
                                        else if(sto==1){
                                            sop.setTexture(sorp);
                                            sto=0;
                                            res=0;
                                        }
                                    }
                                    else if(event.mouseButton.x>=led.getPosition().x&&event.mouseButton.x<led.getPosition().x+led.getGlobalBounds().width&&event.mouseButton.y>=led.getPosition().y&&event.mouseButton.y<led.getPosition().y+led.getGlobalBounds().height){
                                        auto timeinlb=chrono::system_clock::now();
                                        ib0=false;

                                        if(lb==0){
                                            if(sto==0){
                                                sop.setTexture(sorp2);
                                                sto=1;
                                                stoo=1;
                                                tbp=time00;
                                                timenow=time0;
                                                lbp=1;
                                                w2.draw(sop);
                                            }
                                            lb=1;
                                        }
                                        lb=1;
                                        for(i0=0;i0<b12;i0++){
                                            for(i1=0;i1<a12;i1++){
                                                g3[i0][i1].setTexture(rev);
                                            }
                                        }
                                        for(i0=0;i0<b12;i0++){
                                            for(i1=0;i1<a12;i1++){
                                                w2.draw(g3[i0][i1]);
                                            }
                                        }

                                        w2.display();

                                        RenderWindow w3(sf::VideoMode(a12*16,b12*16+50), "Leaderboard");
                                        ifstream sc("files/leaderboard.txt");
                                        score sce[5];
                                        string n50;
                                        i0=0;
                                        while(getline(sc,n50)){
                                            int p1,p2;
                                            p1=n50.find(":");
                                            p2=n50.find(",");
                                            int m1,m2,m3;
                                            m1=stoi(n50.substr(0, p1));
                                            m2=stoi(n50.substr(p1+1, p2-p1-1));
                                            m3=m1*60+m2;
                                            string n1;
                                            n1=n50.substr(p2+2,n50.length()-p2-2);
                                            score tt0;
                                            tt0.name=n1;
                                            tt0.sec=m3;
                                            sce[i0]=tt0;
                                            i0++;
                                        }
                                        if(i0<5||i0>5){
                                            cout<<"leaderboard.txt is wrong";
                                            return 0;
                                        }
                                        for(i0=0;i0<5;i0++){
                                            for(i1=i0+1;i1<5;i1++){
                                                if(sce[i1].sec<sce[i0].sec){
                                                    int ls5=sce[i0].sec;
                                                    string ls50=sce[i0].name;
                                                    sce[i0].sec=sce[i1].sec;
                                                    sce[i0].name=sce[i1].name;
                                                    sce[i1].sec=ls5;
                                                    sce[i1].name=ls50;
                                                }
                                            }
                                        }
                                        while(w3.isOpen()){
                                            Event e20;
                                            while (w3.pollEvent(e20)) {
                                                if (e20.type == Event::Closed) {

                                                    w3.close();
                                                }
                                            }
                                            w3.clear(Color::Blue);
                                            string ltext;
                                            for(i0=0;i0<5;i0++){
                                                int m10=sce[i0].sec/60;
                                                int s10=sce[i0].sec%60;
                                                string ti10;
                                                if(m10<10){
                                                    ti10="0"+to_string(m10)+":";
                                                }
                                                else{
                                                    ti10=""+to_string(m10)+":";
                                                }
                                                if(s10<10){
                                                    ti10=ti10+"0"+to_string(s10);
                                                }
                                                else
                                                {
                                                    ti10=ti10+""+to_string(s10);
                                                }
                                                ltext=ltext+to_string(i0+1)+".\t"+ti10+"\t"+sce[i0].name+"\n\n";
                                            }
                                            Text tboard(ltext, font, 18);
                                            tboard.setFillColor(Color::White);
                                            setText(tboard,(a12*16)/2,(b12*16)/2+20+25);
                                            Text tit("LEADERBOARD", font, 22);
                                            tit.setFillColor(Color::White);
                                            tit.setStyle(Text::Bold);
                                            tit.setStyle(Text::Underlined);
                                            setText(tit,(a12*16)/2,(b12*16)/2+25-120);

                                            w3.clear(Color::Blue);
                                            w3.draw(tit);
                                            w3.draw(tboard);
                                            w3.display();

                                        }
                                        while (w2.pollEvent(event)) {

                                        }
                                        lb=0;
                                        ib0=true;
                                        if(lbp==1){
                                            sto=0;
                                            stoo=0;
                                            sop.setTexture(sorp);
                                        }
                                        //lbp=0;
                                        auto timeoutlb=chrono::system_clock::now();
                                        auto time3=std::chrono::duration_cast<std::chrono::seconds>(timeoutlb-timeinlb);
                                        if(lbp==1){
                                            tst=tst+time3.count();
                                        }

                                        lbp=0;
                                        lb=0;
                                    }
                                }
                            }
                            /*if (event.type==Event::MouseButtonPressed&&event.mouseButton.button==Mouse::Left){
                                int mx=event.mouseButton.x;
                                int my=event.mouseButton.y;

                            }*/

                        }

                        if(worl==0&&sto==0){
                            auto ntime=chrono::system_clock::now();
                            auto time5=std::chrono::duration_cast<std::chrono::seconds>(ntime - st0);
                            time00=time5.count();
                        }
                        time0=time00-tst;
                        if(sto==1&&stoo==0){
                            //btime=chrono::system_clock::now();
                            stoo=1;
                            tbp=time00;
                            timenow=time0;
                            if(res==1){
                                st0=chrono::system_clock::now();
                            }
                        }
                        if(stoo==1&&sto==0){
                            tst=tst+time00-tbp;
                            //etime=chrono::system_clock::now();
                            stoo=0;
                        }

                        /*auto time6=std::chrono::duration_cast<std::chrono::seconds>(etime-btime);
                        if(sto==1){
                            auto a1time=chrono::system_clock::now();
                            auto a2time=chrono::system_clock::now();
                            auto time6=std::chrono::duration_cast<std::chrono::seconds>(a1time-a1time);
                        }
                        if(time6.count()>0){

                            tst=tst+time6.count();
                            btime=chrono::system_clock::now();
                            etime=chrono::system_clock::now();
                        }*/


                        w2.clear(Color::White);
                        //time0=time0-tst;
                        if(sto==1&&res==1){
                            time0=0;
                        }
                        else if(sto==1){
                            time0=timenow;
                        }

                        if(time0>=0){
                            ts1=time0/60/10;
                            ts2=time0/60%10;
                            ts3=time0%60/10;
                            ts4=time0%60%10;
                        }

                        Sprite td1=digitss[ts1];
                        Sprite td2=digitss[ts2];
                        Sprite td3=digitss[ts3];
                        Sprite td4=digitss[ts4];
                        td1.setPosition(a12*32-97,32*(b12+0.5)+16);
                        td2.setPosition(a12*32-76,32*(b12+0.5)+16);
                        td3.setPosition(a12*32-54,32*(b12+0.5)+16);
                        td4.setPosition(a12*32-33,32*(b12+0.5)+16);
                        w2.draw(td1);
                        w2.draw(td2);
                        w2.draw(td3);
                        w2.draw(td4);
                        for(i0=0;i0<b12;i0++) {
                            for(i1=0;i1<a12;i1++) {
                                w2.draw(g2[i0][i1]);
                            }
                        }
                        for(i0=0;i0<b12;i0++) {
                            for(i1=0;i1<a12;i1++) {
                                w2.draw(g0[i0][i1]);

                            }
                        }
                        //Sprite face;
                        //face.setPosition((a12*32)/2-32,b12*32+18);
                        int win=0;
                        int lose=0;
                        for(i0=0;i0<b12;i0++) {
                            for(i1=0;i1<a12;i1++) {
                                if(g1[i0][i1].a==0&&g1[i0][i1].m==0){
                                    win=1;
                                }
                                if(g1[i0][i1].a==1&&g1[i0][i1].m==1){
                                    lose=-1;
                                }
                            }
                        }
                        if(win==0&&lose==0) {

                            score checknew;
                            int isnewtop=0;
                            worl = 1;
                            for (i0 = 0; i0 < b12; i0++) {
                                for (i1 = 0; i1 < a12; i1++) {
                                    if (g1[i0][i1].m == 1) {
                                        g1[i0][i1].flag = 1;
                                        g0[i0][i1].setTexture(flag);
                                        g2[i0][i1].setTexture(hid);
                                        countofmine = 0;
                                        Sprite face(fa2);
                                        face.setPosition((a12 * 32) / 2 - 32, b12 * 32 + 18);
                                        w2.draw(face);
                                        w2.draw(sop);
                                        w2.draw(led);
                                        w2.draw(dbg);

                                        int ls0=0;
                                        Sprite digitsss=digitss[ls0];
                                        digitsss.setPosition(33+0*21, 32*(b12+0.5)+16);
                                        w2.draw(digitsss);
                                        w2.draw(g2[i0][i1]);
                                        w2.draw(g0[i0][i1]);


                                    }
                                }
                            }
                            w2.display();
                            int record012 = 0;
                            ifstream sc("files/leaderboard.txt");
                            score sce[5];
                            string n50;
                            i0 = 0;
                            while (getline(sc, n50)) {
                                int p1, p2;
                                p1 = n50.find(":");
                                p2 = n50.find(",");
                                int m1, m2, m3;
                                m1 = stoi(n50.substr(0, p1));
                                m2 = stoi(n50.substr(p1 + 1, p2 - p1 - 1));
                                m3 = m1 * 60 + m2;
                                string n1;
                                n1 = n50.substr(p2 + 2, n50.length() - p2 - 2);
                                score tt0;
                                tt0.name = n1;
                                tt0.sec = m3;
                                sce[i0] = tt0;
                                i0++;
                            }

                            sc.close();
                            if (ssave != 0) {
                                continue;
                            } else {
                                ssave = 1;
                                int min012 = sce[0].sec;
                                int record012 = 0;
                                for (i0=0;i0<5;i0++) {
                                    if (min012 < sce[i0].sec) {
                                        min012 = sce[i0].sec;
                                        record012 = i0;
                                    }
                                }
                                if (time0<min012) {
                                    score ns0;
                                    ns0.sec = time0;
                                    ns0.name = name;
                                    sce[record012] = ns0;
                                    isnewtop=1;
                                    checknew.sec=time0;
                                    checknew.name=name;
                                }
                                ofstream sc000("files/leaderboard.txt");
                                for(i0=0;i0<5;i0++){
                                    sc000 << setw(2) << setfill('0') << sce[i0].sec / 60 << ":"<< setw(2) << setfill('0') << sce[i0].sec % 60 << ", "<< sce[i0].name << "\n";
                                }
                                sc000.close();
                            }
                            for (i0 = 0; i0 < 5; i0++) {
                                for (i1 = i0 + 1; i1 < 5; i1++) {
                                    if (sce[i1].sec < sce[i0].sec) {
                                        int ls5 = sce[i0].sec;
                                        string ls50 = sce[i0].name;
                                        sce[i0].sec = sce[i1].sec;
                                        sce[i0].name = sce[i1].name;
                                        sce[i1].sec = ls5;
                                        sce[i1].name = ls50;
                                    }
                                }
                            }
                            RenderWindow w3(sf::VideoMode(a12*16,b12*16+50), "Leaderboard");
                            while(w3.isOpen()){
                                Event e20;
                                while (w3.pollEvent(e20)) {
                                    if (e20.type == Event::Closed) {

                                        w3.close();
                                    }
                                }
                                w3.clear(Color::Blue);
                                string ltext;
                                int alrcheck=0;
                                for(i0=0;i0<5;i0++){

                                    int m10=sce[i0].sec/60;
                                    int s10=sce[i0].sec%60;
                                    string ti10;
                                    if(m10<10){
                                        ti10="0"+to_string(m10)+":";
                                    }
                                    else{
                                        ti10=""+to_string(m10)+":";
                                    }
                                    if(s10<10){
                                        ti10=ti10+"0"+to_string(s10);
                                    }
                                    else
                                    {
                                        ti10=ti10+""+to_string(s10);
                                    }
                                    if(isnewtop==1&&checknew.name==sce[i0].name&&checknew.sec==sce[i0].sec&&alrcheck==0){
                                        //cout<<"*"<<i0<<endl;
                                        string nme=sce[i0].name+"*";
                                        //cout<<nme;
                                        ltext=ltext+to_string(i0+1)+".\t"+ti10+"\t"+nme+"\n\n";
                                        alrcheck=1;
                                    }
                                    else {
                                        ltext=ltext+to_string(i0+1)+".\t"+ti10+"\t"+sce[i0].name+"\n\n";
                                    }


                                }
                                Text tboard(ltext, font, 18);
                                tboard.setFillColor(Color::White);
                                setText(tboard,(a12*16)/2,(b12*16)/2+20+25);
                                Text tit("LEADERBOARD", font, 22);
                                tit.setFillColor(Color::White);
                                tit.setStyle(Text::Bold);
                                tit.setStyle(Text::Underlined);
                                setText(tit,(a12*16)/2,(b12*16)/2+25-120);

                                w3.clear(Color::Blue);
                                w3.draw(tit);
                                w3.draw(tboard);
                                w3.display();

                            }
                            while(w2.pollEvent(event)){

                            }

                            isnewtop=0;
                        }else if(win==1&&lose==0){

                            //Sprite face(fa1);
                            face.setPosition((a12*32)/2-32,b12*32+18);
                            w2.draw(face);
                        }
                        else if(lose==-1){
                            worl=-1;
                            for(i0=0;i0<b12;i0++){
                                for(i1=0;i1<a12;i1++){
                                    if(g1[i0][i1].flag==1&&g1[i0][i1].m==1){
                                        Sprite flagwhenlose(flag);
                                        flagwhenlose.setPosition(i1*32,i0*32);
                                        w2.draw(flagwhenlose);
                                    }
                                    if(g1[i0][i1].m==1){
                                        g1[i0][i1].flag=0;
                                        g0[i0][i1].setTexture(rev);
                                        Sprite flagwhenlose(mine);
                                        flagwhenlose.setPosition(i1*32,i0*32);
                                        w2.draw(flagwhenlose);
                                        //ountofmine=0;
                                        Sprite face(fa3);
                                        face.setPosition((a12*32)/2-32,b12*32+18);
                                        w2.draw(face);
                                    }
                                }
                            }
                        }
                        string scount;
                        scount=to_string(countofmine);
                        w2.draw(dbg);
                        if(countofmine>=0){
                            if(scount.length()<3){
                                int ls1=scount.length();
                                for(i1=0;i1<3-ls1;i1++){
                                    scount="0"+scount;
                                }
                            }
                            for(i0=0;i0<scount.length();i0++){
                                string ls=scount.substr(i0,1);
                                int ls0=stoi(ls);
                                Sprite digitsss=digitss[ls0];
                                digitsss.setPosition(33+i0*21, 32*(b12+0.5)+16);
                                w2.draw(digitsss);
                            }
                        }
                        else{

                            minus0.setPosition(33+0*21, 32*(b12+0.5)+16);
                            w2.draw(minus0);
                            if(scount.length()<4){
                                for(i1=0;i1<4-scount.length();i1++){
                                    Sprite digitsss=digitss[0];
                                    digitsss.setPosition(33+(i1+1)*21, 32*(b12+0.5)+16);
                                    w2.draw(digitsss);
                                }
                            }
                            for(i0=1;i0<scount.length();i0++){
                                string ls=scount.substr(i0,1);
                                int ls0=stoi(ls);
                                Sprite digitsss=digitss[ls0];
                                digitsss.setPosition(33+(i0+i1)*21, 32*(b12+0.5)+16);
                                w2.draw(digitsss);
                            }
                        }

                        w2.draw(led);
                        setText(welg,600,250);
                        welg.setFillColor(Color::Black);
                        welg.setStyle(Text::Underlined);
                        setText(com,33,32*(b12+0.5)+16);
                        com.setFillColor(Color::Black);
                        com.setStyle(Text::Underlined);
                        if(sto==0){
                            w2.draw(sop);
                        }
                        else{
                            w2.draw(sop);
                            for(i0=0;i0<b12;i0++) {
                                for(i1=0;i1<a12;i1++) {
                                    w2.draw(g3[i0][i1]);

                                }
                            }
                        }
                        //w2.draw(face);
                        //w2.draw(com);
                        w2.display();
                    }
                }
            }
        }
        setText(ite, a12*32/2, b12*32/2-45);
        cursor.setPosition(ite.getPosition().x + ite.getLocalBounds().width/2, ite.getPosition().y-cursor.getLocalBounds().height/2.0f-ite.getLocalBounds().height/2.0f);
        setText(welsen,a12*32/2,b12*32/2-150);
        setText(ena,a12*32/2,b12*32/2-75);
        window.clear(Color::Blue);
        window.draw(welsen);
        window.draw(ite);
        window.draw(cursor);
        window.draw(ena);
        window.display();
    }
    return 0;
}