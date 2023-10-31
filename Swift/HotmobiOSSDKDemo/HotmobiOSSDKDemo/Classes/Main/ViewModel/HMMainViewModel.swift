//
//  HMMainViewModel.swift
//  HotmobiOSSDKDemo
//
//  Created by Paul Cheung on 4/3/2019.
//  Copyright © 2019 Paul Cheung. All rights reserved.
//

import Foundation
import RxSwift
import RxDataSources
import RxCocoa

class HMMainViewModel {
    var itemList: BehaviorRelay<[SectionModel<String, HMBaseViewModel>]>? = BehaviorRelay(value: [])
    
    func getLocalJSONMain() -> Observable<[HMBaseViewModel]> {
        
        return Observable.create{ (observer) in
            
            let path = HMResourcesLoader.frameworkBundle().path(forResource: "MainJson.js", ofType: "")
            let jsonString = try? String(contentsOfFile: path!)
            let jsonData = jsonString?.data(using: .utf8)
            let responseDict: NSDictionary = try! JSONSerialization.jsonObject(with: jsonData!, options: .mutableContainers) as! NSDictionary
            
            let contentDict: NSDictionary = responseDict.object(forKey: "data") as! NSDictionary
            
            if contentDict != nil {
                var tmpItemList: [HMBaseViewModel] = []
                let itemsList = contentDict.object(forKey: "items") as! NSArray
                for item in itemsList {
                    let jsonString = HMUtilities.objectToString(object: item)
                    let mainModel = HMMainMenuModel(JSONString: jsonString! as String)
                    let mainViewModel = HMMainItemViewModel(model: mainModel!)
                    
                    tmpItemList.append(mainViewModel)
                }
                self.itemList?.accept([SectionModel(model: "", items: tmpItemList)])
                
                observer.onNext(tmpItemList)
                observer.onCompleted()
            }
            else{
            }
            return Disposables.create()
        }
    }
}
