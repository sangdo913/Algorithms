pub trait Summary {
    fn summarize_author(&self) -> String;
    fn summarize(&self) -> String {
        // String::from("(계속 읽기)")
        format!("{}님의 기사 더 읽기", self.summarize_author())
    }
}

pub struct NewsArticle{
    pub headline: String,
    pub location: String,
    pub author: String,
    pub content: String,
}

impl Summary for NewsArticle {
    //비우기: example 14
    // fn summarize(&self) ->String {
    //     format!("{}, by {}, ({})", self.headline, self.author, self.location)
    // }
    //author 추가 : example 14
    fn summarize_author(&self) -> String {
        format!("기자: {}", self.author)
    }
}

pub struct Tweet {
    pub username: String,
    pub content: String,
    pub reply: bool,
    pub retweet: bool,
}

impl Summary for Tweet {
    fn summarize_author(&self) -> String {
        format!("@{}", self.username)
    }

    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
}

pub trait isSummary {
    fn print(&self);
}

impl<T: Summary> isSummary for T {
    fn print(&self) {
        println!("구현되어있습니다!")
    }
}