import System.Environment

main = do
    [f] <- getArgs
    input <- readFile f
    putStr "8.1: "
    print $ sum $ metadata 1 $ map read $ words input
    putStr "8.2: "
    print $ value $ map read $ words input

metadata :: Int -> [Int] -> [Int]
metadata c [] = []
metadata 1 (a:b:xs) = (take b $ drop cl xs) ++  metadataOrEmpty cl a xs
                      where cl = childLength a xs
metadata c (a:b:xs) = (metadata 1 (a:b:xs)) ++ (metadata (c-1) $ drop cl (a:b:xs))
                      where cl = childLength 1 (a:b:xs)

metadataOrEmpty :: Int -> Int -> [Int] -> [Int]
metadataOrEmpty 0 a xs = []
metadataOrEmpty c a xs = metadata a xs

childLength :: Int -> [Int] -> Int
childLength c [] = 0
childLength 0 (a:b:xs) = 0
childLength 1 (0:b:xs) = 2 + b
childLength 1 (a:b:xs) = (childLength a xs) + 2 + b
childLength c (a:b:xs) = cl + (childLength (c-1) $ drop cl (a:b:xs))
                         where cl = childLength 1 (a:b:xs)

value :: [Int] -> Int
value [] = 0
value (0:b:xs) = sum $ take b xs
value (a:b:xs) = childValues [i | i <- (take b $ drop cl xs), i <= a ] xs
                 where cl = childLength a xs

childValues :: [Int] -> [Int] -> Int
childValues [] _ = 0
childValues (i:is) (x:xs) = (childValues is (x:xs)) + value (findChild i (x:xs))

findChild :: Int -> [Int] -> [Int]
findChild 1 (x:xs) = (x:xs)
findChild i (x:xs) = findChild (i-1) $ drop cl (x:xs)
                     where cl = childLength 1 (x:xs)

