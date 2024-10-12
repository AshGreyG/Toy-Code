function main() {
    const deviceWidth = device.width;
    const deviceHeight = device.height;
    auto();
    app.launch("com.netease.cloudmusic");
    var mainActivity = text("我的").find();
    while (mainActivity.empty()) {
        mainActivity = text("我的").find();
        sleep(200);
    }
    click("我的");

    // Click the fans list. Notice fans button cannot be clicked,
    // so I use the bounds click.

    var mineActivity = text("粉丝").find();
    while (mineActivity.empty()) {
        mineActivity = text("粉丝").find();
        sleep(200);
    }
    var fansButtonRect = text("粉丝").findOnce().bounds();
    click(fansButtonRect.centerX(), fansButtonRect.centerY());



    var fansOfUni = text("回关").find();
    var fansOfBi  = text("互相关注").find();
    while (fansOfUni.empty() && fansOfBi.empty()) {
        fansOfUni = text("回关").find();
        fansOfBi  = text("互相关注").find();
        if (textContains("网络设置").find().nonEmpty()) {
            toast("Net Error. Script ends.");
            return;
        }
        sleep(200);
    }
    var endActivity = text("为你推荐").find();
    while (endActivity.empty() || fansOfUni.nonEmpty()) {
        fansOfUni.forEach(fan => {
            let uniRect = fan.bounds();
            click(uniRect.centerX() + 100, uniRect.centerY());
            sleep(1000);
            click("移除粉丝");
            sleep(1000);
            click("移除");
            sleep(1000);
        });
        swipe(deviceWidth / 2.0, deviceHeight / 2.0 + 400,
              deviceWidth / 2.0, deviceHeight / 2.0 - 400, 200);
        fansOfUni = text("回关").find();
        endActivity = text("为你推荐").find();
    }
    return;
}

main();