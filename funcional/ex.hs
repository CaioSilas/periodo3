import Prelude

import Data.Char

count :: (a -> Bool) -> [a] -> Int
count _ [] = 0
count f xs = length(filter f xs)

divide :: Int -> [a] -> ([a], [a])
divide  [] = ([], [])
divide n xs = divideAcc n xs []
    where 
        divideAcc  [] _ = ([], [])
        divideAcc 0 (x:[]) ys = (ys, [x])
        divideAcc n (x : xs) ys 
            | n == 0 = (ys, x:xs)
            | otherwise = divideAcc (n-1) xs (ys++[x])