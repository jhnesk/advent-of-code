import System.Environment

main = do
    [f] <- getArgs
    input <- readFile f
    print $ sum $ metadata 1 $ map read $ words input

metadata :: Int -> [Int] -> [Int]
metadata c [] = []
metadata c [a] = []
metadata 1 (a:b:xs) = 
        (take b $ drop cl xs) ++  metadataOrEmpty cl a xs
    where cl = childLength a xs
metadata c (a:b:xs) = (metadata 1 (a:b:xs)) ++ (metadata (c-1) (drop (childLength 1 (a:b:xs)) (a:b:xs)))

metadataOrEmpty :: Int -> Int -> [Int] -> [Int]
metadataOrEmpty 0 a xs = []
metadataOrEmpty c a xs = metadata a xs

childLength :: Int -> [Int] -> Int
childLength c [] = 0
childLength c [a] = 0
childLength 0 (a:b:xs) = 0
childLength 1 (0:b:xs) = 2 + b
childLength 1 (a:b:xs) = (childLength a xs) + 2 + b
childLength c (a:b:xs) = cl + (childLength (c-1) (drop (cl) (a:b:xs)))
            where cl = childLength 1 (a:b:xs)





