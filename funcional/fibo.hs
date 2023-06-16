import Prelude

import Data.Char




fibo :: Int -> Int
fibo 0 = 0
fibo 1 = 1
fibo x = fibo(x - 1) + fibo(x - 2)

conj :: Bool -> Bool -> Bool
conj False False = False
conj False True = False
conj True False = False
conj True True = True


calxor :: Bool-> Bool -> Bool
calxor False False = False
calxor True True = False
calxor _ _ = True

existsPositive :: [Int] -> Bool
existsPositive [] = False
existsPositive (x : xs) = if x > 0 then True else existsPositive xs


minList :: [Int] -> Maybe Int
minList [] = nothing
minList [x] = just x
minList (x : xs) = min x (minList xs)

andList :: [Bool] -> Bool
andList [] = True
andList (x : xs) = x && andList xs

orList :: [Bool] -> Bool
orList [] = False
orList (x : xs) = x || orList xs

indexOf :: Int -> [Int] -> Int
indexOf _ [] = 0
indexOf a (x : xs) = ac a (x : xs) 0
    where
        ac _ [] _ = 0
        ac a [x] _
            | a == x = 0
            | otherwise = -1
        ac a (x : xs) p 
            | a == x = p
            | otherwise = ac a (xs) (p+1)

removeAll :: Int -> [Int] -> [Int]
removeAll _ [] = []
removeAll x (y : ys)
        | x == y = removeAll x ys
        | otherwise = y : removeAll x ys

capitalize :: String -> String
capitalize [] = []
capitalize a = map toUpper a

removePrimo :: [Int] -> [Int]
removePrimo [] = []
removePrimo (x : xs) = filter (\x -> not (isPrime x)) xs
    where
        isPrime x = (length (factors x)) == 2
        factors x = [y | y <- [1..x],  x `mod` y == 0]

{-all :: (a -> Bool) -> [a] -> Bool
all = foldr step []
    where
        step f ac = filter ac-}

all :: (a -> Bool) -> [a] -> Bool
all f a 
    | length(filter(f) a) == 0 = True
    | otherwise = False



        

    
        
        