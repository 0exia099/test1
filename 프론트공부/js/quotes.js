const quotes = [{quote: "a", author:"aa"},
{quote: "b", author:"aa"},
{quote: "c", author:"aa"},
{quote: "d", author:"aa"},
{quote: "e", author:"aa"}]

const quote = document.querySelector("#quote span:first-child");
const author = document.querySelector("#quote span:last-child");

const todayQuote = quotes[Math.floor(Math.random() * quotes.length)];
quote.innerText = todayQuote.quote;
author.innerText = todayQuote.author;