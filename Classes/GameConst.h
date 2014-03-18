#pragma once

const int kLineCutFix = 1;

#define macro_isipad (EGLView::getInstance()->getFrameSize().height/EGLView::getInstance()->getFrameSize().width <= 1.334f)
#define macro_isiphone5  (EGLView::getInstance()->getFrameSize().height/EGLView::getInstance()->getFrameSize().width >= 1.6f)
#define macro_isiphone4 (EGLView::getInstance()->getFrameSize().height/EGLView::getInstance()->getFrameSize().width > 1.334f && EGLView::getInstance()->getFrameSize().height/EGLView::getInstance()->getFrameSize().width < 1.6f)

#define ccp_percent(x, y) Point(Director::getInstance()->getWinSize().width*(x)/100.0f, Director::getInstance()->getWinSize().height*(y)/100.0f)
#define x_percent(x) (Director::getInstance()->getWinSize().width*(x)/100.0f)
#define y_percent(y) (Director::getInstance()->getWinSize().height*(y)/100.0f)

static const char SAVE_GAME[] = "savegame.dat";

static const char CAMERA_IMAGE[] = "camera.png";

#define macro_document_temp  ((FileUtils::getInstance()->getWritablePath() + "temp").c_str())

#define UD_Gold       "gold"
#define UD_RateTime   "ratetime"

static const int kAnimTag_Anim = 100;
static const int kAnimTag_Shake = 101;

//priorities
const int kPriority_Low = -200;
const int kPriority_Medium = -300;
const int kPriority_High = -400;

#define Notification_Score          "Notification_Score"
#define Notification_Gold           "Notification_Gold" 

#define Notification_RateOrShareFin "Notification_RateOrShareFin"

#define Leaderboard_HighScore_Bird "com.lotfun.abuse.bird"

#define Leaderboard_HighScore_Pant "com.lotfun.abuse.pant"

#define Leaderboard_HighScore_Ninja "com.lotfun.abuse.ninja"

#define IAP_0_99 "com.lotfun.flysomething.0.99"

static const int kIAP_Reward = 50000;

static const int kRateShare_Reward = 500;


const int kLifeCoin_Arr[] = {
    1500,
    30000,
    99999,
};

static const int kDodgeGameObsNum = 20;

static const int kBgMoveSpeed = 20;
