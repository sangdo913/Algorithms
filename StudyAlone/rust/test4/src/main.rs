fn main() { 
    // example10_1();
    // example10_3();
    // example10_4();
    // example10_9();
    // example10_11();
    // example10_13();
    // example10_14();
    // example10_15();
    // example_extra();
    // example10_20();
    // example10_23();
    // example10_25();
    static_lifetime();
}

fn example10_1() {
    println!("Hello, world!"); 
    // let number_list = vec![34,50,25,100,65];
    let number_list = vec![102,34,6000,89,54,2,43,8];

    let mut largest = number_list[0];

    for number in number_list {
        if number > largest {
            largest = number;
        }
    }

    println!("가장 큰 숫자: {}", largest);
}

/////////// example 3 /////////////////////////////////////////////////////
// fn largest(list: &[i32]) -> i32 {
//     let mut largest = list[0];

//     for &item in list.iter() {
//         if item > largest {
//             largest = item;
//         }
//     }
//     largest
// }

// fn example10_3() {
//     let number_list = vec![34,50,25,100,65];

//     let result = largest(&number_list);
//     println!("가장 큰 숫자: {}", result);

//     let number_list = vec![102,34,6000,89, 54, 2, 43, 8];

//     let result = largest(&number_list);
//     println!("가장 큰 숫자 : {}", result);
// }
////////////////////////////////////////////////////////////////

/* not generic */
// fn largest_i32(list:&[i32]) -> i32 {
//     let mut largest = list[0];
    
//     for &item in list.iter() {
//         if item > largest {
//             largest = item;
//         }
//     }

//     largest
// }
// fn largest_char(list: &[char]) -> char{
//     let mut largest = list[0];

//     for &item in list.iter() {
//         if item > largest {
//             largest = item;
//         }
//     }

//     largest
// }

// fn example10_4(){
//     let number_list = vec![34,50,25,100,65];

//     let result = largest_i32(&number_list);
//     println!("가장 큰 숫자: {}", result);

//     let char_list = vec!['y', 'm', 'a', 'q'];

//     let result = largest_char(&char_list);

//     println!("가장 큰 문자: {}", result);
// }
/* end */

/* generic -compile error */
// fn largest<T>(list: &[T]) -> T {
//     let mut largest = list[0];

//     for &item in list.iter() {
//         if item > largest {
//             largest = item;
//         }
//     }

//     largest;
// }
/* end */

/* generic in structure */
// struct Point<T> {
//     x: T,
//     y: T,
// }

// fn example10_6() {
//     let integer = Point { x: 5, y: 10};
//     let float = Point { x: 1.0, y: 4.0};

//     //different type error
//     // let wont_work = Point { x: 5, y: 4.0 };
// }
/*end */

/* two type are different*/
struct Point<T,U> {
    x: T,
    y: U,
}

fn example10_8() {
    let both_integer = Point { x: 5, y: 10};
    let both_float = Point { x: 1.0, y: 4.0 };

//     OK
    let integer_and_float = Point { x: 5, y: 4.0 };
}

/*  
열거자
enum Option<T> {
    Some<T>,
    None;
}

enum Result<T, E> {
    Ok(T),
    Err(E),
}
*/

/* method  generic*/
struct Point2<T> {
    x: T,
    y: T,
}

impl<T> Point2<T> {
    fn x(&self) -> &T {
        &self.x
    }
}

//example 10-10
impl Point2<f32> {
    fn distance_from_origin(&self) -> f32{
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}

fn example10_9(){
    let p = Point2 {x: 5, y: 10};

    println!("p.x = {}", p.x());

    //example 10-10
    let p2:Point2<f32> = Point2 {x:5.0, y: 5.0};
    println!("distacne_from_origin {}", p2.distance_from_origin());
}
/* end */

/* 구조체의 정의와는 다른 제네릭 타입을 사용하는 메서드 */
struct Point3<T,U> {
    x: T,
    y: U,
}

impl<T,U> Point<T,U> {
    fn mixup<V, W> (self, other: Point<V,W>) -> Point<T,W> {
        Point {
            x: self.x,
            y: other.y,
        }
    }
}

fn example10_11() {
    let p1 = Point{ x: 5, y: 10.4 };
    let p2 = Point { x: "Hello", y: 'c'};

    let p3 = p1.mixup(p2);
    println!("p3.x = {}, p3.y = {}", p3.x, p3.y);
}
/* end */

/* 트레이트 */
//example 10-12

use test::Summary;
use graph::NewsArticle;
use graph::Tweet;

fn example10_13(){
    let tweet = graph::Tweet {
        username: String::from("horse_ebooks"),
        content: String::from("러스트 언어 공부를 시작했습니다."),
        reply: false,
        retweet: false,
    };

    println!("새 트윗 1개: {}", tweet.summarize());
}
/* end */

fn example10_14(){
    let article = NewsArticle {
        headline: String::from("대한민국, 러시아 월드컵 예선에서 독일을 이겼다."),
        location: String::from("카잔 아레나, 러시아"),
        author: String::from("위키백과"),
        content: String::from("2018년 6월 27일 러시아 카잔의 카잔 아레나에서 열린 2018 월드컵 F조 3차전 경기에서 대한민국이 독일에 2:0 승리를 거뒀다."),
    };
    //비우기 테스트
    println!("새로운 기사: {}", article.summarize());
}

/*end*/


/*트레이트 경계*/
/*
pub fn notify<T: Summary>(item: T)
*/
use std::fmt::Display;
use std::fmt::Debug;

pub fn notify(item: impl Summary + Display) {
}
//same
/*
pub fn notify<T:Summary + Display>(item: T) {
}
*/

/*where 절*/
// fn some_function<T: Display + Clone, U: Clone + Debug>(t: T, u: U) -> i32 {
//     0
// }
fn some_function<T,U>(t: T, u: U) -> i32 
where T: Display + Clone,
    U: Clone + Debug
{
    0
}
/*end*/

/*트레이트를 구현하는 값 리턴하기*/
fn returns_summarizable() -> impl Summary {
    Tweet {
        username: String::from("horse_ebooks"),
        content: String::from("러스트 언어 공부를 시작했습니다."),
        reply: false,
        retweet: false,
    }
}

/* error : 454페이지 */
// fn returns_summarizable(switch: bool) -> impl Summary {
//     if (switch) {
//         Tweet {
//             username: String::from("horse_ebooks"),
//             content: String::from("러스트 언어 공부를 시작했습니다."),
//             reply: false,
//             retweet: false,
//         }
//     } else {
//         NewsArticle {
//             headline: String::from("headline"),
//             location: String::from("location"),
//             author: String::from("author"),
//             content: String::from("content"),
//         }
//     }
// }

/*example 10-15*/
fn largest10_15<T:PartialOrd + Copy>(list: &[T]) -> T {
    let mut largest = list[0];

    for &item in list.iter() {
        if item > largest {
            largest = item;
        }
    }

    return largest;
}

fn largest_my<T:PartialOrd>(list: &[T]) -> &T {
    let mut largest = &list[0];

    for item in list.iter() {
        if item > largest {
            largest = item;
        }
    }
    return largest
}

fn example10_15(){
    let number_list = vec![34,50,25,100,65];

    // let result = largest10_15(&number_list);
    let result = largest_my(&number_list);
    println!("가장 큰 숫자: {}", result);

    let char_list = vec!['y', 'm', 'a', 'q'];

    // let result = largest10_15(&char_list);
    let result = largest_my(&char_list);

    println!("가장 큰 문자: {}", result);
}


struct Pair<T> {
    x: T,
    y: T,
}

impl<T> Pair<T> {
    fn new (x: T, y: T) -> Self {
        Self {
            x,
            y,
        }
    }
}


impl<T: Display + PartialOrd> Pair<T> {
    fn cmp_display(&self) {
        if self.x >= self.y {
            println!("가장 큰 멤버는 x: {}", self.x);
        } else {
            println!("가장 큰 멤버는 y = {}", self.y);
        }
    }
}

use graph::isSummary;

/* Summary가 구현되면 print 가능*/
// impl<T: Display> Summary for Pair<T> {
//     fn summarize_author(&self) -> String{
//         format!("{} {}", self.x, self.y)
//     }
// }

fn example_extra(){
    let tweet = Tweet{
        username: String::from("user"),
        content:String::from("content"),
        reply:false,
        retweet:false
    };
    tweet.print();

    /* error */
    let p:Pair<i32> = Pair{
        x:10,
        y:32
    };
    //Summary가 구현되면 사용 가능
    // p.print()
}

/* 두 개의 문자열 슬라이스 중 길이가 긴 것을 리턴하는 longest 호출*/
/* error: 수명 문제 */
// fn longest10_20(x: &str, y:&str) -> &str {
//     if x.len() > y.len() {
//         x
//     } else {
//         y
//     }
// }

fn longest10_20_life<'a>(x: &'a str, y:&'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}

fn example10_20() {
    let string1 = String::from("abcd");
    let string2 = "xyz";

    let result = longest10_20_life(string1.as_str(), string2);
    println!("더 긴 문자열: {}", result);
}
/* 다른 수명을 가진 문자열의 참조를 longest 함수에 전달 */

fn example10_23() {
    let string1 = String::from("abcd");

    {
        let string2 = "xyz";

        let result = longest10_20_life(string1.as_str(), string2);
        println!("더 긴 문자열: {}", result);
    }
}

/* error: string2의 수명이 result까지 가지 못함 */
// fn example10_24() {
//     let string1 = String::from("abcd");
//     let result;
//     {
//         let string2 = String::from("xyz");
//         result = longest10_20_life(string1.as_str(), string2.as_str());
//     }
//     println!("더 긴 문자열: {}", result);
// }

/* 컴파일 되지 않는 코드*/
// fn longest<'a>(x: &str, y: &str) -> &'a str {
//     let result = String::from("아주 긴 문자열");

//     let res = result.as_str();
//     res
// }

struct ImportantExcerpt<'a> {
    part: &'a str,
}

fn example10_25() {
    let novel = String::from("스타워즈. 오래 전 멀고 먼 은하계에....");
    let first_sentence = novel.split('.')
    .next()
    .expect("문장에서 마침표'.'를 찾을 수 없습니다.");
    println!("{}", first_sentence);
    let i = ImportantExcerpt{part:first_sentence};
}

/*  수명의 생략 */
fn first_word(s: &str) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }
    return &s[..]
}
/*
1. 각 참조 매개 변수마다 수명 매개변수를 만든다.
2. 명시적으로 하나의 매개변수가 있으면 입력 수명을 모든 출력 수명 매개변수에 적용한다.
3. 입력 수명 매개변수가 하나 이상이며, 함수가 메서드로 선언되어서 매개변수 중 하나가 &serlf 나 &mut self 일때는, self 변수의 수명을 모든 출력 수명 매개변수에 적용한다.
*/
// //1번 적용

fn first_word1<'a> (s: &'a str) -> &str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }
    return &s[..]
}

// 2번 적용
fn first_word2<'a> (s: &'a str) -> &'a str {
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }
    return &s[..]
}

//error : 출력 수명 매개변수가 없음
// fn longest (x: & str, y: & str) -> & str{
//      if x.len() < y.len() {
//          return x 
//      }
//      return y
// }

/* 메서드 정의에서의 수명 애노테이션 */
impl<'a> ImportantExcerpt<'a> {
    fn level(&self) -> i32{
        3
    }
}

/* 3번 생략 예제*/ 
impl<'a> ImportantExcerpt<'a> {
    fn announce_and_return_part(&self, announcement: &str) -> &str {
        println!("주목해주세요! {}", announcement);
        self.part
    }
}

/*1번 규칙*/
// impl<'a> ImportantExcerpt<'a> {
//     fn announce_and_return_part<'b, 'c>(&'b self, announcement: &'c str) -> &str {
//         println!("주목해주세요! {}", announcement);
//         self.part
//     }
// }

/* 3번 규칙*/
// impl<'a> ImportantExcerpt<'a> {
//     fn announce_and_return_part<'b, 'c>(&'b self, announcement: &'c str) -> &'b str {
//         println!("주목해주세요! {}", announcement);
//         self.part
//     }
// }

/* 정적 수명 */
fn static_lifetimetest<'a> ()-> &'a str{
    let s: &str = "문자열은 정적 수명이다.";
    return s

    //error static에 life가 더 짧은 string.as_str()을 넣을 수 없다.
    // let string= String::from("스트링 문자열");
    // let literal: &'static str = string.as_str();
    // return literal
}

fn static_lifetime(){
    println!("{}", static_lifetimetest());
}

/*제네릭 타입 매개변수, 트레이트 경계, 그리고 수명*/
fn longest_with_an_announcement<'a, T> (x:&'a str, y: &'a str, ann: T) -> &'a str
where T: Display
{
    println!("주목하세요: {}", ann);
    if x.len() > y.len() {
        return x
    } else {
        return y
    }
}

fn test<'a> (x: &'a str) ->&str{
    return x
}

// fn test<'a> (x: &'a str, y: &'a str) -> &str {
//     return x
// }