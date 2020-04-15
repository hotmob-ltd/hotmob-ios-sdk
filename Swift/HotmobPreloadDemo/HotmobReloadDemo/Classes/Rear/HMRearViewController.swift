//
//  HMRearViewController.swift
//  HotmobReloadDemo
//
//  Created by Paul Cheung on 8/4/2019.
//  Copyright © 2019 Paul Cheung. All rights reserved.
//

import UIKit
import RxSwift
import RxCocoa
import RxDataSources
import SWRevealViewController

class HMRearViewController: HMBaseViewController, UITableViewDelegate {
    
    var presentedRow: Int = 0
    @IBOutlet weak var rearTableView: UITableView!
    var rearViewModel: HMRearViewModel? = HMRearViewModel()
    private let RearItemCellID = "HMRearItemTableViewCell"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Do any additional setup after loading the view.
        
        self.title = "Rear View"
        
        self.setupTableView()
        self.getRearItems()
    }
    
    func getRearItems(){
        self.rearViewModel?.getLocalJSONRear()
            .subscribe(onNext: { (_) in
            }, onError: { (error) in
            }).disposed(by: self.disposeBag)
    }
    
    func setupTableView(){
        self.rearTableView.register(UINib(nibName: self.RearItemCellID, bundle: HMResourcesLoader.frameworkBundle()), forCellReuseIdentifier: self.RearItemCellID)
        self.rearTableView.register(UITableViewCell.self, forCellReuseIdentifier: "DefaultCellID")
        self.rearTableView.rx.setDelegate(self).disposed(by: disposeBag)
        
        let dataSource = RxTableViewSectionedReloadDataSource<SectionModel<String, HMRearCatItemViewModel>>(configureCell: { [unowned self] (ds, tv, indexPath, model) in
            let cellModel: HMRearCatItemViewModel = model
            let cell = tv.dequeueReusableCell(withIdentifier: self.RearItemCellID)! as! HMRearItemTableViewCell
            
            cell.viewModel = cellModel
            return cell
            },titleForHeaderInSection: { ds, index in
            return ds.sectionModels[index].model
        }
        )
        
        self.rearViewModel?.itemList?.asObservable()
            .bind(to: self.rearTableView.rx.items(dataSource: dataSource))
            .disposed(by: self.disposeBag)
        
        self.rearTableView.rx
            .itemSelected
            .subscribe(onNext: { [unowned self] (indexPath) in
                let sectionTitle = dataSource.sectionModels[indexPath.section].model
                
                print("indexPath = \(indexPath)")
                let revealController: SWRevealViewController = self.revealViewController()
                
                let row = indexPath.row
                if row == self.presentedRow {
                    revealController.setFrontViewPosition(FrontViewPosition.left, animated: true)
                }else if row == 2 {
                    revealController.setFrontViewPosition(FrontViewPosition.rightMost, animated: true)
                }else if row == 3 {
                    revealController.setFrontViewPosition(FrontViewPosition.right, animated: true)
                }
                
                var vc: UIViewController? = nil
                switch sectionTitle{
                case "Normal":
                    vc = HMMainViewController()
                    break
                case "TabBar":
                    vc = HMTabBarViewController()
                    break
                default:
                    break
                }
                if vc != nil {
                    let nav = UINavigationController(rootViewController: vc!)
                    revealController.pushFrontViewController(nav, animated: true)
                    self.presentedRow = row
                }
            }).disposed(by: self.disposeBag)
    }
}
