package        main
 
import (
        "fmt"
        "strconv"
        "os"
        "github.com/skorobogatov/input"
)
 
type Lexem struct {
    Tag
    Image string
}
 
type Tag int
 
const (
    ERROR Tag = 1 << iota  // Неправильная лексема
    NUMBER                 // Целое число
    VAR                    // Имя переменной
    PLUS                   // Знак +
    MINUS                  // Знак -
    MUL                    // Знак *
    DIV                    // Знак /
    LPAREN                 // Левая круглая скобка
    RPAREN                 // Правая круглая скобка
)
 
type stack []int
func (s *stack) Push(l int) { *s=append(*s, l) }
func (s stack) Top() (l int) { return s[len(s)-1] }
func (s *stack) Pop() (l int) {
        stack := *s
        x := stack[len(stack)-1]
        *s=stack[:len(stack)-1]
        return x
}
 
var ok bool
var ls stack
var lexem Lexem
var cache map[string]int
 
func isalnum(x uint8) bool {
        if x>47 && x<58 { return true }
        return false
}
 
func isalpha(x uint8) bool {
        if (x>96 && x<124) || (x>64 && x<89){ return true }
        return false
}
       
func lexer(expr string, lexems chan Lexem) {
        var l Lexem
        for i:=0;i<len(expr);i++ {
                switch {
                        case expr[i] == ' ': continue
                        case expr[i] == '+': l.Tag = PLUS;   l.Image = "+";
                        case expr[i] == '-': l.Tag = MINUS;  l.Image = "-";
                        case expr[i] == '*': l.Tag = MUL;    l.Image = "*";
                        case expr[i] == '/': l.Tag = DIV;    l.Image = "/";
                        case expr[i] == '(': l.Tag = LPAREN; l.Image = "(";
                        case expr[i] == ')': l.Tag = RPAREN; l.Image = ")";
                        case isalnum(expr[i]):
                                j := i 
                                for (i<len(expr)) && isalnum(expr[i]) { i++ }
                                l.Tag = NUMBER; l.Image = expr[j:i]
                                i--
                        case isalpha(expr[i]):
                                j := i 
                                for (i<len(expr)) && (isalnum(expr[i]) || isalpha(expr[i])) { i++ }
                                l.Tag = VAR; l.Image = expr[j:i]
                                i--
                        default: l.Tag = ERROR
                }
                lexems <- l
        }
        close(lexems)
}
 
func E(lexems chan Lexem){
        T(lexems)
        E2(lexems)
}
 
func T(lexems chan Lexem){
        F(lexems)
        T2(lexems)
}
 
func E2(lexems chan Lexem){
        lx:=lexem
        if (lx.Tag & (PLUS | MINUS)) != 0 {
                lexem, ok =<-lexems
                T(lexems)
                if lx.Tag==MINUS { ls.Push(-1*ls.Pop()) }
                E2(lexems)
                if lx.Tag==MINUS { ls.Push(-1*ls.Pop()) }
                x:=ls.Pop()
                if lx.Tag==PLUS { ls.Push(ls.Pop()+x)
                }else { ls.Push(ls.Pop()-x) }
        }
}
func T2(lexems chan Lexem){
        lx:=lexem
        if lx.Tag & (MUL | DIV) != 0 {
                lexem, ok =<-lexems
                F(lexems)
                if lx.Tag==MUL { ls.Push(ls.Pop()*ls.Pop())
                }else{
                        x:=ls.Pop()
                        ls.Push(ls.Pop()/x)
                }
                T2(lexems)
        }
}
func F(lexems chan Lexem){
        switch lexem.Tag{
                case NUMBER:
                        value, _ := strconv.Atoi(lexem.Image)
                        ls.Push(value)
                        lexem, ok = <- lexems
                case LPAREN:
                        lexem, ok = <- lexems
                        E(lexems)
                        if lexem.Tag != RPAREN {
                                fmt.Printf("error\n")
                                os.Exit(1)
                        }
                        lexem, ok = <- lexems
                case VAR:
                        value, found := cache[lexem.Image]; if !found {
                                input.Scanf("%d", &value)
                                cache[lexem.Image] = value
                        }
                        ls.Push(value)
                        lexem, ok = <- lexems
                case MINUS:
                        lexem, ok = <- lexems
                        F(lexems)
                        ls.Push(-1*ls.Pop())
        }
}
func main(){
        defer func () {
                if x := recover(); x != nil {
                        fmt.Printf("error\n")
                        os.Exit(1)
                }
        }()
        lexems := make(chan Lexem)
        s := input.Gets()
        cache=make(map[string]int,  len(s)/2)
        go lexer(s, lexems)
        lexem, ok  = <-lexems
        E(lexems)
        if ok {
                fmt.Printf("error\n")
                os.Exit(1)
        }
        x:=ls.Pop()
        fmt.Printf("%d\n", x)
}